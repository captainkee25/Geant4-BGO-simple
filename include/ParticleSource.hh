#ifndef PARTICLESOURCE_HH
#define PARTICLESOURCE_HH

#include "G4VUserPrimaryGeneratorAction.hh" //inheritor class
#include "G4ParticleDefinition.hh" //to be able to access defintions of particles like electrons, protons etc.
#include "G4ParticleGun.hh" //to shoot particle! hands up!
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"

class ParticleSource : public G4VUserPrimaryGeneratorAction
{
public:
    ParticleSource();
    virtual ~ParticleSource();   

    virtual void GeneratePrimaries(G4Event* event) override;
    G4ThreeVector GetSourcePosition() const;

private:
    G4ParticleGun* fParticleGun;
    G4ThreeVector fSourcePosition;
};

#endif