#include "DetectorConstruction.hh"
#include "ParticleSource.hh"


//Defining the variables of this inherited DetectorConstruction class
DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

void DetectorConstruction::DefineMaterials()
{
	//NIST Manager
	G4NistManager* nist = G4NistManager::Instance();
    worldMat = nist -> FindOrBuildMaterial("G4_AIR");
    bgo	= nist -> FindOrBuildMaterial("G4_BGO");
	teflon	= nist -> FindOrBuildMaterial("G4_TEFLON");
    plastic = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
}


G4LogicalVolume* DetectorConstruction::BuildCrystal(G4LogicalVolume* motherLV, const G4ThreeVector& pos, G4RotationMatrix* rot, int copyNo)
{
    G4bool checkOverlaps = true;
    // Crystal dimensions
    G4double BGOWidth  = 3*cm;
    G4double BGOLength = 21.0*cm;

    // BGO solid
    const G4double r_inner_BGO[] = {0, 0};
    const G4double r_outer_BGO[] = {BGOWidth, BGOWidth};
    const G4double z_BGO[]       = {0,BGOLength};


    G4Polyhedra* BGO_S = new G4Polyhedra("BGO_S", 0., 2*CLHEP::pi, 6, 2, z_BGO, r_inner_BGO, r_outer_BGO);
    G4LogicalVolume* fCrystals_LV = new G4LogicalVolume(BGO_S, bgo, "BGO_LV");

    // Visualization
    G4VisAttributes* BGOVisAtt = new G4VisAttributes(G4Colour(0,1,1));
    BGOVisAtt->SetForceSolid(true);
    fCrystals_LV->SetVisAttributes(BGOVisAtt);

    // Place BGO inside mother volume
    new G4PVPlacement(
        rot,
        pos,
        fCrystals_LV,
        "BGO",
        motherLV,
        false,
        0,
        checkOverlaps
    );

    // Wrapping: teflon
    G4double teflonThickness = 0.23*mm;
    const G4double r_inner[] = {BGOWidth, BGOWidth};
    const G4double r_outer[] = {BGOWidth + teflonThickness, BGOWidth + teflonThickness};
    
    const G4double z_wrap[]  = {0,BGOLength};
    G4Polyhedra* wrap_S = new G4Polyhedra("Wrap_S", 0., 2*CLHEP::pi, 6, 2, z_wrap, r_inner, r_outer);
    G4LogicalVolume* wrap_LV = new G4LogicalVolume(wrap_S, teflon, "Wrap_LV");
    wrap_LV->SetVisAttributes(new G4VisAttributes(G4Colour(1,1,0)));

    // Place wrapping inside the crystal LV
    new G4PVPlacement(
        0,
        G4ThreeVector(0,0,0),
        wrap_LV,
        "Wrapping",
        fCrystals_LV,
        false,
        copyNo,
        checkOverlaps
    );

    return fCrystals_LV;
}

void DetectorConstruction::DefineVolumes()
{
    G4bool checkOverlaps = true;
    G4double xWorld = 48.6 *cm; //can only use these units because we called the System of Units header. Otherwise standard is mm
    G4double yWorld = 38 *cm;
    G4double zWorld = 13.5 *cm;

    G4Box * solidWorld = new G4Box("solidWorld",0.5*xWorld,0.5*yWorld,0.5*zWorld); //g4box parameters is object name, half of length, width and height
    G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld,worldMat,"logicalWorld");
    physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalWorld,"physWorld",0,false,0,checkOverlaps);


    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateY(-90*deg);
    
    G4RotationMatrix* rotMid = new G4RotationMatrix();
    rotMid->rotateY(-90*deg);
    rotMid->rotateZ(-30*deg);

    crystal1 = BuildCrystal(logicalWorld, G4ThreeVector(0.,0.,1.848*cm), rotMid,1);
    crystal2 = BuildCrystal(logicalWorld, G4ThreeVector(0.,6*cm,-1.75*cm), rot,2);
    crystal3 = BuildCrystal(logicalWorld, G4ThreeVector(0.,-6.5*cm,-1.75*cm), rot,3);

    
    G4Box* casingSolid = new G4Box("casingSolid",1*cm,0.5*cm,0.025*cm); 
    G4LogicalVolume *casingLogical = new G4LogicalVolume(casingSolid,plastic,"casingLogical");
    G4VPhysicalVolume *casing = new G4PVPlacement(0,G4ThreeVector(12.125*cm, 0*cm, -2.25*cm),casingLogical,"casing",logicalWorld,false,0,checkOverlaps);
}


G4VPhysicalVolume *DetectorConstruction::Construct()
{
    DefineMaterials();
    DefineVolumes();
    return physWorld;

}

void DetectorConstruction::ConstructSDandField(){
        auto sdManager = G4SDManager::GetSDMpointer();
    
        // Create ONE SD that can handle multiple crystals
        SensitiveDetector* bgoSD = new SensitiveDetector("BGOSD");
        sdManager->AddNewDetector(bgoSD);
    
        // Attach SD to all 3 crystals
        crystal1->SetSensitiveDetector(bgoSD);
        crystal2->SetSensitiveDetector(bgoSD);
        crystal3->SetSensitiveDetector(bgoSD);
        
};

// Note: Epic simulation uses an additional DefineCrystalMV to create a logical volume slightly bigger to check overlaps
