//
/// \file SiCEDEventAction.cc
//

#include "SiCEDEventAction.hh"
#include "SiCEDRunAction.hh"
#include "SiCEDAnalysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDEventAction::SiCEDEventAction(SiCEDRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDEventAction::~SiCEDEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDEventAction::BeginOfEventAction(const G4Event* event)
{    
    G4int eventID = event->GetEventID();
    G4cout << "\n---> Begin of event: " << eventID << G4endl;

    edep_total=0.;
    edep_device=0.;

    x_device=0, y_device=0, z_device=0;

    x_EdepC_device=0., y_EdepC_device=0., z_EdepC_device=0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDEventAction::EndOfEventAction(const G4Event* event)
{   
    G4int eventID = event->GetEventID();

    //Note : Only one particle emits per event
    px = event->GetPrimaryVertex(0)->GetPrimary()->GetPx();
    py = event->GetPrimaryVertex(0)->GetPrimary()->GetPy();
    pz = event->GetPrimaryVertex(0)->GetPrimary()->GetPz();

    x_device = x_EdepC_device/edep_device;
    y_device = y_EdepC_device/edep_device;
    z_device = z_EdepC_device/edep_device;
  
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, eventID);

    analysisManager->FillNtupleDColumn(1, edep_total);
    analysisManager->FillNtupleDColumn(2, edep_device);

    analysisManager->FillNtupleDColumn(3, x_device);
    analysisManager->FillNtupleDColumn(4, y_device);
    analysisManager->FillNtupleDColumn(5, z_device);

    analysisManager->FillNtupleDColumn(6, px);
    analysisManager->FillNtupleDColumn(7, py);
    analysisManager->FillNtupleDColumn(8, pz);

    analysisManager->AddNtupleRow();


    G4cout << "\n---> End of event: " << eventID << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
