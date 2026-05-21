//
/// \file SiCEDDetectorConstruction.hh

#ifndef SiCEDDetectorConstruction_h
#define SiCEDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4GenericMessenger.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class SiCEDDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SiCEDDetectorConstruction();
    virtual ~SiCEDDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    void SetMaterial(G4String matName);
    G4String GetMaterialName() const { return fMaterialName; }

    void SetEnergyLabel(G4String label) { fEnergyLabel = label; }
    G4String GetEnergyLabel() const { return fEnergyLabel; }

  protected:
    G4VPhysicalVolume* fDevicePV;
    G4LogicalVolume*   fDeviceLogicVol;

  private:
    G4GenericMessenger* fMessenger;
    G4String            fMaterialName;
    G4String            fEnergyLabel;
    G4Material*         fSiMat;
    G4Material*         fSiCMat;

    void DefineCommands();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
