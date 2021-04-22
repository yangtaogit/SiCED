
//
/// \file SiCEDRunAction.cc
//

#include "SiCEDRunAction.hh"
#include "SiCEDPrimaryGeneratorAction.hh"
#include "SiCEDDetectorConstruction.hh"
#include "SiCEDAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDRunAction::SiCEDRunAction()
: G4UserRunAction(),
  fTotalEdep(0.)
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // add new units for SiCED
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "SiCED", milligray);
  new G4UnitDefinition("microgray", "microGy" , "SiCED", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "SiCED", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "SiCED", picogray); 

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in JMQAnalysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Creating ntuple
  analysisManager->CreateNtuple("SiCED", "Energe deposition in SiC Device");
  analysisManager->CreateNtupleDColumn("EventID");

  analysisManager->CreateNtupleDColumn("Edep_total");
  
  analysisManager->CreateNtupleDColumn("Edep_device");

  analysisManager->CreateNtupleDColumn("Device_center_x");
  analysisManager->CreateNtupleDColumn("Device_center_y");
  analysisManager->CreateNtupleDColumn("Device_center_z");
  analysisManager->CreateNtupleDColumn("Particle_momentum_x");
  analysisManager->CreateNtupleDColumn("Particle_momentum_y");
  analysisManager->CreateNtupleDColumn("Particle_momentum_z");
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDRunAction::~SiCEDRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  G4String fileName = "SiCED_5um";
  analysisManager->OpenFile(fileName);

  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) {
    G4cout << "nofEvents = " << nofEvents << G4endl;
    return;
  }

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


