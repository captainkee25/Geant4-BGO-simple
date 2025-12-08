#include "PhysicsList.hh"

//Register Physics is a function from the modular physics list that adds Em interactions

PhysicsList::PhysicsList() //Can just do this in the header itself, but nice to keep clean
{
    RegisterPhysics(new G4EmStandardPhysics_option4()); 
    RegisterPhysics(new G4RadioactiveDecayPhysics()); 
    RegisterPhysics(new G4DecayPhysics()); 
}

PhysicsList::~PhysicsList(){}

