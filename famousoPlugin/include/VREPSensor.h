#pragma once

#include <v_repLib.h>
#include <config.h>

#include <ostream>

class VREPSensor : protected config::Famouso::Publisher{
  private:
    const simInt mId;
  public:
    VREPSensor(simInt id, const famouso::mw::Subject& subject) 
      : config::Famouso::Publisher(subject), mId(id) 
    {}
    VREPSensor(const VREPSensor&&);
    virtual ~VREPSensor();
    virtual void update() = 0;
    simInt id() const{return mId;}
    std::string name() const {return simGetObjectName(mId);}
    const famouso::mw::Subject& subject() const {return config::Famouso::Publisher::subject();}
};

std::ostream& operator<<(std::ostream& out, const VREPSensor& sensor); 
