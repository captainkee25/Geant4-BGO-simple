#include "ParticleSource.hh"

ParticleSource::ParticleSource()
{
    
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    fSourcePosition = G4ThreeVector(12.125*cm, 0*cm, -2.25*cm);

    //Give all this to the particle gun. Can also add things like polarization
    fParticleGun -> SetParticlePosition(fSourcePosition);
    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0*m,0*m,0*m));

}

G4ThreeVector ParticleSource::GetSourcePosition() const
{
    return fSourcePosition;
}

ParticleSource::~ParticleSource(){delete fParticleGun;}

void ParticleSource::GeneratePrimaries(G4Event *anEvent)
{
        G4int Z = 11;        // Sodium
        G4int A = 22;        // Mass number

        G4double charge = 0.*eplus;
        G4double E = 0.*keV; // initial kinetic energy (i.e. at rest)

        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,E);
        fParticleGun -> SetParticleDefinition(ion);
        fParticleGun -> SetParticleCharge(charge);    
        fParticleGun -> SetParticleEnergy(E);
    
    fParticleGun ->GeneratePrimaryVertex(anEvent); //Does the actual shooting. Member function of the Particle Gun class
}