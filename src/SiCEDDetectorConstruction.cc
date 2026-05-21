//
/// \file SiCEDDetectorConstruction.cc

#include "SiCEDDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4GenericMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDDetectorConstruction::SiCEDDetectorConstruction()
: G4VUserDetectorConstruction(),
  fDevicePV(nullptr), fDeviceLogicVol(nullptr),
  fMaterialName("SiC"), fEnergyLabel("2200keV"),
  fSiMat(nullptr), fSiCMat(nullptr)
{
  DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDDetectorConstruction::~SiCEDDetectorConstruction()
{
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDDetectorConstruction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this, "/SiCED/det/", "Detector geometry control");
  fMessenger->DeclareMethod("setMaterial",
                            &SiCEDDetectorConstruction::SetMaterial,
                            "Set device material: Si or SiC")
            .SetStates(G4State_PreInit, G4State_Idle);
  fMessenger->DeclareProperty("setEnergyLabel", fEnergyLabel,
                              "Label for output filename, e.g. 546keV or 2200keV")
            .SetStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDDetectorConstruction::SetMaterial(G4String matName)
{
  fMaterialName = matName;
  if (fDeviceLogicVol && fSiMat && fSiCMat) {
    G4Material* mat = (fMaterialName == "Si") ? fSiMat : fSiCMat;
    fDeviceLogicVol->SetMaterial(mat);
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    G4cout << "Device material changed to: " << fMaterialName << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiCEDDetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  // --- Materials ---
  fSiMat = nist->FindOrBuildMaterial("G4_Si");

  if (!fSiCMat) {
    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* C  = nist->FindOrBuildElement("C");
    fSiCMat = new G4Material("SiC", 3.2*g/cm3, 2);
    fSiCMat->AddElement(Si, 50*perCent);
    fSiCMat->AddElement(C,  50*perCent);
  }

  G4Material* deviceMat = (fMaterialName == "Si") ? fSiMat : fSiCMat;
  G4cout << "Device material: " << fMaterialName << G4endl;

  // --- World ---
  G4double world_sizeXY = 5.*cm, world_sizeZ = 5.*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* world_box = new G4Box("World",
                               0.5*world_sizeXY,
                               0.5*world_sizeXY,
                               0.5*world_sizeZ);

  G4LogicalVolume* world_logic = new G4LogicalVolume(world_box, world_mat, "World");

  G4VPhysicalVolume* world_phy = new G4PVPlacement(0,
                                                   G4ThreeVector(),
                                                   world_logic,
                                                   "World",
                                                   0,
                                                   false,
                                                   0,
                                                   checkOverlaps);

  // --- Device: 100 µm thick slab ---
  G4double device_sizeX = 0.5*cm;
  G4double device_sizeY = 0.5*cm;
  G4double device_sizeZ = 100.*um;   // 100 µm

  G4Box* device_box = new G4Box("Device",
                                0.5*device_sizeX,
                                0.5*device_sizeY,
                                0.5*device_sizeZ);

  fDeviceLogicVol = new G4LogicalVolume(device_box, deviceMat, "Device");

  fDevicePV = new G4PVPlacement(0,
                                G4ThreeVector(0, 0, 0),
                                fDeviceLogicVol,
                                "Device",
                                world_logic,
                                false,
                                0,
                                checkOverlaps);

  return world_phy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
