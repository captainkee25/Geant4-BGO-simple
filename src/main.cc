#include <iostream>

#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIterminal.hh"

#include "PhysicsList.hh"
#include "ParticleSource.hh"
#include "DetectorConstruction.hh"
#include "ActionInit.hh"


int main(int argc,char** argv)
{
    G4MTRunManager *runManager = new G4MTRunManager;

    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInit());
    

    G4VisManager * visManager = new G4VisExecutive;
    visManager->Initialize();

    //UI stuff- change depending on which server you're running on (headless or nah)
    G4UImanager * UI = G4UImanager::GetUIpointer();  
    
    // Execute macro file passed as first argument
    G4String macroFile = argv[1];
    UI->ApplyCommand("/control/execute " + macroFile);
    
    delete visManager;
    delete runManager;
    return 0;
}