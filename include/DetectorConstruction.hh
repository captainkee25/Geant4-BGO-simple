#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh" //standard parent class to inherit from

#include "G4Box.hh"
#include "G4Polyhedra.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Material.hh"
#include "G4NistManager.hh" //necessary class to define materials

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//Just for visualizing the BGOs
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//For sensitive detection BGOs
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"


class DetectorConstruction: public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction(); //constructor
        virtual ~DetectorConstruction(); //when overriding functions, good practice to redefine destructor for child

        virtual G4VPhysicalVolume *Construct() override; //use virtual to override functions that are alr defined in the inherited class


    private:
        void DefineMaterials();
        void DefineVolumes();
        G4LogicalVolume* BuildCrystal(G4LogicalVolume* motherLV,
            const G4ThreeVector& pos,
            G4RotationMatrix* rot,int copyNo);
    
        G4LogicalVolume* crystal1;
        G4LogicalVolume* crystal2;
        G4LogicalVolume* crystal3;

        G4Material* worldMat;
        G4Material* bgo;
        G4Material* teflon;
        G4Material* plastic;
        
        G4VPhysicalVolume* physWorld;

        virtual void ConstructSDandField();

};

//Construct(): builds detector geometry and returns the "world volume" containing all the others
//in the G4User...class, this is empty/abstract. We are replacing it with our PhysicalVolume 
#endif