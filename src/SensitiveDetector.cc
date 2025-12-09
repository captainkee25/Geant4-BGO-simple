#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name):G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector(){}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    for(int i=0; i<3; ++i)
    {
        fEnergyDeposited[i] = 0.;
        fEntryTime[i] = -1.;  // initialize with -1 to indicate not yet hit
    }
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //when the photon enters the detector 
    G4double energyDeposited = aStep->GetTotalEnergyDeposit();

    int copyNo = preStepPoint->GetTouchable()->GetCopyNumber();

    if(fEntryTime[copyNo] < 0.)
    fEntryTime[copyNo] = preStepPoint->GetGlobalTime();

    fEnergyDeposited[copyNo] += energyDeposited;

    return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    for(int i=1; i<=3; ++i) 
    {
        G4double E = fEnergyDeposited[i];
        G4double t = fEntryTime[i];

        analysisManager->FillNtupleIColumn(0, eventID);
        analysisManager->FillNtupleIColumn(1, i);          
        analysisManager->FillNtupleDColumn(2, E);
        analysisManager->FillNtupleDColumn(3, t);  
        analysisManager->AddNtupleRow();        // entry time after decay start
    }   

    for(int i=1; i<=3; ++i) {
        analysisManager->FillH1(i-1, fEnergyDeposited[i]);  // IDs: 0,1,2
    }
}