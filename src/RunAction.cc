#include "RunAction.hh"

RunAction::RunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    
    for (int i = 0; i<3;++i)
    {
        G4String hname = "Edep BGO" + std::to_string(i+1); 
        analysisManager->CreateH1(hname, "Energy deposit", 4096, 0., 2 * MeV);
    }

    analysisManager->CreateNtuple("BGO", "BGO crystals");
    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleIColumn("crystalID");          
    analysisManager->CreateNtupleDColumn("EnergyDeposited");;
    analysisManager->CreateNtupleDColumn("EntryTime");;  
    analysisManager->FinishNtuple();
}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("EnergyHists" + strRunID.str() + ".root");
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();
    
    G4int runID = run->GetRunID();
    G4cout << "Finishing run " << runID << G4endl;
}