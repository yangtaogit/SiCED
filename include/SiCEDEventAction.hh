//
/// \file SiCEDEventAction.hh
/// \brief Definition of the SiCEDEventAction class

#ifndef SiCEDEventAction_h
#define SiCEDEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class SiCEDRunAction;
class G4Event;

/// Event action class
///

class SiCEDEventAction : public G4UserEventAction
{
  public:
    SiCEDEventAction(SiCEDRunAction* runAction);
    virtual ~SiCEDEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void RecordTotal(G4double edep);

    void RecordDevice(G4double edep, 
		G4double point_in_x, G4double point_in_y, G4double point_in_z,
		G4double point_out_x, G4double point_out_y, G4double point_out_z);

  private:
    SiCEDRunAction* fRunAction;

    G4double px=0, py=0, pz=0;

    G4double edep_total=0.;
    G4double edep_device=0.;


    G4double x_device=0, y_device=0, z_device=0;

    G4double x_EdepC_device=0, y_EdepC_device=0, z_EdepC_device=0;
};


inline void SiCEDEventAction::RecordTotal(G4double edep) {
    
    edep_total += edep; 

}

inline void SiCEDEventAction::RecordDevice( G4double edep,
                                            G4double point_in_x, G4double point_in_y, G4double point_in_z,
                                            G4double point_out_x, G4double point_out_y, G4double point_out_z)
{
    edep_device += edep; 

    x_EdepC_device += edep*(point_out_x+point_in_x)/2;
    y_EdepC_device += edep*(point_out_y+point_in_y)/2;
    z_EdepC_device += edep*(point_out_z+point_in_z)/2;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
