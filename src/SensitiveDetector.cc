#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name):G4VSensitiveDetector(name){}

SensitiveDetector::~SensitiveDetector(){}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    for(int i=0; i<3; ++i)
    {
        fEnergyDeposited[i] = 0.;
        fEntryTime[i] = -1.;  // initialize with -1 to indicate not yet hit
        fStopped[i] = true;
    }
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // per step, get the total energy deposit, and assign it to the crystal that's being stepped in
    // energy deposit accumulated and saved per event 
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();  
    G4double energyDeposited = aStep->GetTotalEnergyDeposit();

    int copyNo = preStepPoint->GetTouchable()->GetCopyNumber();

    if(fEntryTime[copyNo-1] < 0.)
    fEntryTime[copyNo-1] = preStepPoint->GetGlobalTime();

    fEnergyDeposited[copyNo-1] += energyDeposited;

    G4Track* track = aStep->GetTrack();
    if(track->GetTrackStatus()!=fStopAndKill)
        fStopped[copyNo-1]=false;

    return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4double Esmeared[3] = {0., 0., 0.}; //Added this because need it to save for event coincidence

    for(int i=0; i<3; ++i) 
    {
        G4double E = fEnergyDeposited[i];
        G4double t = fEntryTime[i];
        G4double s = fStopped[i];

        analysisManager->FillNtupleIColumn(0, eventID);
        analysisManager->FillNtupleIColumn(1, i+1);          
        analysisManager->FillNtupleDColumn(2, E);
        analysisManager->FillNtupleDColumn(3, t);
        analysisManager->FillNtupleIColumn(4,s); 

        const G4double relResolution = 0.10;  // 10%

        if (E > 0.) {
        G4double sigma = relResolution * E;
        Esmeared[i] = G4RandGauss::shoot(E, sigma);
        Esmeared[i] = std::max(0.0, Esmeared[i]); 
        
        analysisManager->FillNtupleDColumn(5,Esmeared[i]);}
        
        analysisManager->AddNtupleRow();       


        if (fEnergyDeposited[i] > 0.){  // only plot hits
        analysisManager->FillH1(i, fEnergyDeposited[i]);
        analysisManager->FillH1(i+3, Esmeared[i]);}}
    
        
    G4bool isCoincidence511 = false;
    if(fEnergyDeposited[0] > 0)  
    {G4double t1 = fEntryTime[0];
    if((fEnergyDeposited[1] > 0. && fEntryTime[1] - t1 < 1.5*microsecond)||
        (fEnergyDeposited[2] > 0. && fEntryTime[2] - t1 < 1.5*microsecond))
        {isCoincidence511 = true;}}
    
    if(isCoincidence511)
        {
            analysisManager->FillH1(6, Esmeared[1]); // BGO2 coincidence
            analysisManager->FillH1(7, Esmeared[2]); // BGO3 coincidence
        }

            
    G4bool isCoincidence1275 = false;
    if(fEnergyDeposited[0] > 1*MeV)  
    {G4double t1 = fEntryTime[0];
    if((fEnergyDeposited[1] > 0. && fEntryTime[1] - t1 < 1.5*microsecond)||
        (fEnergyDeposited[2] > 0. && fEntryTime[2] - t1 < 1.5*microsecond))
        {isCoincidence1275 = true;}}
        
    if(isCoincidence1275)
        {
            analysisManager->FillH1(8, Esmeared[0]);
            analysisManager->FillH1(9, Esmeared[1]); // BGO2 coincidence
            analysisManager->FillH1(10, Esmeared[2]); // BGO3 coincidence
        }

}