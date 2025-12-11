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
        analysisManager->AddNtupleRow();       
        
        if (fEnergyDeposited[i] > 0.)  // only plot hits
            analysisManager->FillH1(i, fEnergyDeposited[i]);
        
    }   
}