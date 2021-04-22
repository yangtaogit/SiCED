//
/// \file SiCEDDetectorConstruction.cc
//

#include "SiCEDDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Element.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDDetectorConstruction::SiCEDDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDDetectorConstruction::~SiCEDDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiCEDDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

 
                     
  //     
  // World
  // 
  G4double world_sizeXY = 5.*cm, world_sizeZ = 5.*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
 
  G4Box* world_box = new G4Box("World", 
                                0.5*world_sizeXY, 
                                0.5*world_sizeXY, 
                                0.5*world_sizeZ);

  G4LogicalVolume* world_logic = new G4LogicalVolume(world_box,            
                                                    world_mat,            
                                                    "World");         

  G4RotationMatrix *rotBox = new G4RotationMatrix();
  rotBox->rotateX(0.*deg);

  G4VPhysicalVolume* world_phy = new G4PVPlacement(0,              
                                                  G4ThreeVector(),
                                                  world_logic,     
                                                  "World",        
                                                  0,              
                                                  false,          
                                                  0,              
                                                  checkOverlaps); 


  //     
  // SiC Device Shape 
  //
 
  //G4Material* device_mat = nist->FindOrBuildMaterial("G4_Si");

  // SiC material define
  G4double sic_density = 3.2*g/cm3;
  G4Element* silicon = nist->FindOrBuildElement("Si");
  G4Element* carbon = nist->FindOrBuildElement("C");

  G4Material* SiC =  new G4Material("SiC",sic_density,2);
  SiC->AddElement(silicon,50*perCent);
  SiC->AddElement(carbon,50*perCent);


  G4double device_sizeX = 0.5*cm, device_sizeY = 0.5*cm,device_sizeZ = 0.0005*cm;
  G4ThreeVector device_pos = G4ThreeVector(0, 0, 0);
               
  G4Box* device_box = new G4Box("Device",
                                0.5*device_sizeX,
                                0.5*device_sizeY,
                                0.5*device_sizeZ); 
                      
  G4LogicalVolume* device_logic = new G4LogicalVolume(device_box,         
                                                      SiC,          
                                                      "Device");           

  fDevicePV = new G4PVPlacement(0,                 
                                device_pos,              
                                device_logic,             
                                "Device",                
                                world_logic,             
                                false,                  
                                0,                      
                                checkOverlaps);         

  
  //
  //always return the physical World
  //
  return world_phy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
