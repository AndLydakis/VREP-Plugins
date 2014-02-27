#pragma once

#include <config.h>
#include <mw/common/Event.h>
#include <VREPObject.h>

class VREPSensor : public VREPObject{
  private:
    config::Famouso::Publisher pub;
  protected:
    typedef famouso::mw::Event Event;
    virtual void print(std::ostream& out) const;
    void publish(const Event& e);
  public:
    typedef famouso::mw::Subject Subject;
    VREPSensor(simInt id, const Subject& subject);
    VREPSensor(const VREPSensor& copy);
    virtual ~VREPSensor();
    const Subject& subject() const;
};
