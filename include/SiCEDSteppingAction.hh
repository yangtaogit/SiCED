//
/// \file SiCEDSteppingAction.hh
/// \brief Definition of the SiCEDSteppingAction class

#ifndef SiCEDSteppingAction_h
#define SiCEDSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "SiCEDDetectorConstruction.hh"

class SiCEDEventAction;
class G4Step;


/// Stepping action class
/// 

class SiCEDSteppingAction : public G4UserSteppingAction
{
  public:
    SiCEDSteppingAction( const SiCEDDetectorConstruction* detectorConstruction,
                        SiCEDEventAction* eventAction);
    virtual ~SiCEDSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    const SiCEDDetectorConstruction* fDetConstruction;
    SiCEDEventAction*  fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
