//Protect to ensure it doesnt redefine it each time
#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include <G4VModularPhysicsList.hh> //allows you to combine multiple physics library modularly
#include <G4EmStandardPhysics_option4.hh> //electromagentic physics
#include <G4RadioactiveDecayPhysics.hh>
#include <G4DecayPhysics.hh>

class PhysicsList : public G4VModularPhysicsList //inherit from this
{
public:
//Constructor and destructor classes
    PhysicsList();
    ~PhysicsList();

};

#endif //just include since we have an if statement beginning