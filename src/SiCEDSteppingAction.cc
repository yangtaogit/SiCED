//
/// \file SiCEDSteppingAction.cc
//

#include "SiCEDSteppingAction.hh"
#include "SiCEDEventAction.hh"
#include "SiCEDDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "SiCEDDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDSteppingAction::SiCEDSteppingAction( const SiCEDDetectorConstruction* detectorConstruction,
                                        SiCEDEventAction* eventAction)
: G4UserSteppingAction(),
  fDetConstruction(detectorConstruction),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDSteppingAction::~SiCEDSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDSteppingAction::UserSteppingAction(const G4Step* step)
{
  
  G4double edep = step->GetTotalEnergyDeposit();
  G4StepPoint* point_pre  = step->GetPreStepPoint() ;
  G4StepPoint* point_post = step->GetPostStepPoint() ;
  G4ThreeVector point_in  = point_pre->GetPosition();
  G4ThreeVector point_out = point_post->GetPosition();
   
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  auto volume_name = volume->GetName();

  fEventAction->RecordTotal(edep);

  if( volume_name == "Device"){

    fEventAction->RecordDevice(edep,
                                 point_in[0], point_in[1], point_in[2],
                                 point_out[0], point_out[1],point_out[2]);

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

