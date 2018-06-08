#include "MyDetectorConstruction.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4SubtractionSolid.hh"

MyDetectorConstruction::MyDetectorConstruction(){

}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  
  // Envelope params
  //
 // G4double env_sizeXY = 20*m, env_sizeZ = 30*m;
  //G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  
  //     
  // World
  //
  G4double world_sizeXYZ = 200*cm;
//  G4double world_sizeXY = 1.2*env_sizeXY;
//  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "LogicalWorld");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "PhysicalWorld",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

 

  //Lets try to build material from NIST database
//Ti Foil
G4Box *TiFoil = new G4Box("TiFoil",2.5*cm,2.5*cm,0.0027*cm);
  G4Material *Ti=nist->FindOrBuildMaterial("G4_Ti");
  G4LogicalVolume *logicalTiFoil = new G4LogicalVolume(TiFoil,Ti,"LogicalTiFoil");
  G4VPhysicalVolume *phyTiFoil = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,30*cm),
                            logicalTiFoil,
                            "PhysicalTiFoil",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
//Al Foil1
G4Box *AlFoil = new G4Box("AlFoil",3*cm,3*cm,0.0018*cm);
  G4Material *Al=nist->FindOrBuildMaterial("G4_Al");
  G4LogicalVolume *logicalAlFoil = new G4LogicalVolume(AlFoil,Al,"LogicalAlFoil");
  G4VPhysicalVolume *phyAlFoil = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,39.*cm),
                            logicalAlFoil,
                            "PhysicalAlFoil",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
//DRZ-1

G4Box *DRZ1 = new G4Box("DRZ1",3*cm,3*cm,0.0250*cm);
  G4Material *Gd=nist->FindOrBuildMaterial("G4_Gd");
  G4LogicalVolume *logicalDRZ1 = new G4LogicalVolume(DRZ1,Gd,"LogicalDRZ1");
  G4VPhysicalVolume *phyDRZ1 = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,39.0268*cm),
                            logicalDRZ1,
                            "PhysicalDRZ1",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
//Object
/*G4Box *AlBox = new G4Box("AlBox",3.5*cm,3.5*cm,3*cm);
 // G4Material *Al=nist->FindOrBuildMaterial("G4_Al");
  G4LogicalVolume *logicalAlBox = new G4LogicalVolume(AlBox,Al,"LogicalAlBox");
  G4VPhysicalVolume *phyAlBox = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,65*cm),
                            logicalAlBox,
                            "PhysicalAlBox",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
*/
//Subtracted tube
G4Tubs *CuTube = new G4Tubs("CuTubs",0,0.1*cm,2.5*cm,0.,2*M_PI);
G4Box *BrassBox = new G4Box("BrassBox",2*cm,2*cm,2.5*cm);
G4VSolid* subtract = new G4SubtractionSolid("Box-Tube", BrassBox, CuTube, 0, G4ThreeVector(0.*cm,0.,0.));
G4Material *Cu=nist->FindOrBuildMaterial("G4_Cu");

G4LogicalVolume *subtractedBrassBox = new G4LogicalVolume(subtract,Cu,"SubtractedBrassBox");
G4VPhysicalVolume *phySubtractedBrassBox = new G4PVPlacement(0,
                                 G4ThreeVector(0.,0.,65*cm),
                                 subtractedBrassBox,
                                "PhysicalSubtractedBrassBox",
                                 logicWorld,
                                 false,
                                 0,
                                 checkOverlaps);

//Al Foil2
G4Box *AlFoil2 = new G4Box("AlFoil2",3*cm,3*cm,0.0018*cm);
  
  G4LogicalVolume *logicalAlFoil2 = new G4LogicalVolume(AlFoil2,Al,"LogicalAlFoil2s");
  G4VPhysicalVolume *phyAlFoil2 = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,70*cm),
                            logicalAlFoil2,
                            "PhysicalAlFoil2",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
//DRZ3

G4Box *DRZ3 = new G4Box("DRZ3",7.5*cm,7.5*cm,0.0250*cm);
 // G4Material *Gd=nist->FindOrBuildMaterial("G4_Gd");
  G4LogicalVolume *logicalDRZ3 = new G4LogicalVolume(DRZ3,Gd,"LogicalDRZ3");
  G4VPhysicalVolume *phyDRZ3 = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,70.0268*cm),
                            logicalDRZ3,
                            "PhysicalDRZ3",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);











	return physWorld;

}
