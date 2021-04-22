//
/// \file SiCEDDetectorConstruction.hh
//

#ifndef SiCEDDetectorConstruction_h
#define SiCEDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class SiCEDDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SiCEDDetectorConstruction();
    virtual ~SiCEDDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();


  protected:

    G4VPhysicalVolume*  fDevicePV;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

