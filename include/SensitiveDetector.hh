#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4HCofThisEvent.hh"

#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4String);
    ~SensitiveDetector();

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

    virtual void Initialize(G4HCofThisEvent*hce) override;
    virtual void EndOfEvent(G4HCofThisEvent *hce) override;

    G4double fEnergyDeposited[3];
    G4double fEntryTime[3];
    G4bool fStopped[3];

};

#endif