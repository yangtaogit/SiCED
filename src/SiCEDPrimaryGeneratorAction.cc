//
/// \file SiCEDPrimaryGeneratorAction.cc
//

#include "SiCEDPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "math.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDPrimaryGeneratorAction::SiCEDPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.5*cm));

  fParticleGun->SetParticleEnergy(0.546*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiCEDPrimaryGeneratorAction::~SiCEDPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiCEDPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  // G4double direction_theta = acos(G4UniformRand());
  // if( G4UniformRand() < 0.5){ direction_theta = M_PI-direction_theta; };
  // G4double direction_phi = G4UniformRand()*M_PI*2;

  // G4double direction_x = sin(direction_theta)*cos(direction_phi)*cm;
  // G4double direction_y = sin(direction_theta)*sin(direction_phi)*cm;
  // G4double direction_z = cos(direction_theta)*cm;

  G4double direction_x = 0.*cm;
  G4double direction_y = 0.*cm;
  G4double direction_z = -1.*cm;
  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(direction_x,direction_y,direction_z));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

