#include "RunAction.hh"

RunAction::RunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    
    // true energy hists
    for (int i = 0; i<3;++i)
    {
        G4String hname = "Edep BGO" + std::to_string(i+1); 
        analysisManager->CreateH1(hname, "Energy deposit", 4096, 0., 2.5 * MeV);
    }

    // smeared energy hists
    for (int i = 0; i < 3; ++i)
    {
        G4String hname = "Edep_BGO_smeared" + std::to_string(i+1); 
        analysisManager->CreateH1(hname, "Smeared energy deposit", 4096, 0., 2.5 * MeV);
    }


    // Coincidences 511
    for (int i = 1; i < 3; ++i)
    {
        G4String hname = "Edep_BGO_coincidence_511" + std::to_string(i+1); 
        analysisManager->CreateH1(hname, "Smeared energy deposit", 4096, 0., 2.5 * MeV);
    }

    // Coincidences 1275
    for (int i = 0; i < 3; ++i)
    {
        G4String hname = "Edep_BGO_coincidence_1275" + std::to_string(i+1); 
        analysisManager->CreateH1(hname, "Smeared energy deposit", 4096, 0., 2.5 * MeV);
    }


    analysisManager->CreateNtuple("BGO events", "BGO crystals");
    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleIColumn("crystalID");          
    analysisManager->CreateNtupleDColumn("EnergyDeposited");
    analysisManager->CreateNtupleDColumn("EntryTime");  
    analysisManager->CreateNtupleIColumn("TrackStopped");  
    analysisManager->CreateNtupleDColumn("SmearedEnergy");  
    analysisManager->FinishNtuple();
}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);

    G4int runID = run->GetRunID();

    analysisManager->OpenFile("Readout.root");
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->Write();
    analysisManager->CloseFile();
    
    G4int runID = run->GetRunID();
    G4cout << "Finishing run " << runID << G4endl;
}