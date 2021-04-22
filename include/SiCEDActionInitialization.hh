//
/// \file SiCEDActionInitialization.hh
//

#ifndef SiCEDActionInitialization_h
#define SiCEDActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class SiCEDDetectorConstruction;

class SiCEDActionInitialization : public G4VUserActionInitialization
{
  public:
    SiCEDActionInitialization( SiCEDDetectorConstruction* );
    virtual ~SiCEDActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    SiCEDDetectorConstruction* fDetConstruction;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
