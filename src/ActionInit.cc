#include "ActionInit.hh"

ActionInit::ActionInit(){}

ActionInit::~ActionInit(){}

void ActionInit::BuildForMaster() const
{}

void ActionInit::Build() const
{
    ParticleSource *generator = new ParticleSource();
    SetUserAction(generator); //taken from User Action Initialize class- put in what the generator is
}
