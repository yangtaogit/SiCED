//
/// \file SiCEDActionInitialization.cc
/// \brief Implementation of the SiCEDActionInitialization class

#include "SiCEDActionInitialization.hh"
#include "SiCEDPrimaryGeneratorAction.hh"
#include "SiCEDRunAction.hh"
#include "SiCEDEventAction.hh"
#include "SiCEDSteppingAction.hh"
#include "SiCEDDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDActionInitialization::SiCEDActionInitialization
                          (SiCEDDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDActionInitialization::~SiCEDActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDActionInitialization::BuildForMaster() const
{
  SiCEDRunAction* runAction = new SiCEDRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDActionInitialization::Build() const
{
  SetUserAction(new SiCEDPrimaryGeneratorAction);

  SiCEDRunAction* runAction = new SiCEDRunAction;
  SetUserAction(runAction);
  
  SiCEDEventAction* eventAction = new SiCEDEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new SiCEDSteppingAction(fDetConstruction,eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
