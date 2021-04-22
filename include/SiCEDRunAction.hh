//
/// \file SiCEDRunAction.hh
//

#ifndef SiCEDRunAction_h
#define SiCEDRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the SiCED in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed SiCED is then printed on the screen.

class SiCEDRunAction : public G4UserRunAction
{
  public:
    SiCEDRunAction();
    virtual ~SiCEDRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double fTotalEdep); 

  private:
  
    G4double fTotalEdep;

};

#endif

