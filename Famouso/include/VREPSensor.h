#pragma once

#include <v_repLib.h>
#include <config.h>

#include <ostream>

class VREPSensor : protected config::Famouso::Publisher{
  private:
    const simInt mId;
  protected:
    virtual void print(std::ostream& out) const;
  public:
    VREPSensor(simInt id, const famouso::mw::Subject& subject);
    VREPSensor(const VREPSensor& copy);
    VREPSensor& operator=(const VREPSensor& copy) = delete;
    virtual ~VREPSensor(){}
    virtual void update() = 0;
    simInt id() const{return mId;}
    std::string name() const {return simGetObjectName(mId);}
    const famouso::mw::Subject& subject() const {return config::Famouso::Publisher::subject();}
  friend std::ostream& operator<<(std::ostream&, const VREPSensor&);
};

std::ostream& operator<<(std::ostream& out, const VREPSensor& sensor);
