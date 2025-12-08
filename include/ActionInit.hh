#ifndef ACTIONINIT_HH
#define ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"

#include "ParticleSource.hh"

class ActionInit : public G4VUserActionInitialization
{
public:
    ActionInit();
    virtual ~ActionInit();

    //for multithread modes
    virtual void BuildForMaster() const override;
    virtual void Build() const override;
};

#endif