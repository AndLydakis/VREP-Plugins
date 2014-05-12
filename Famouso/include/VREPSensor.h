#pragma once

#include <config.h>
#include <SensorDataPublisher.h>
#include <VREPObject.h>

template<typename SensorEvent>
class VREPSensor : public VREPObject{
  private:
    SensorDataPublisher<config::Famouso::EL, SensorEvent> pub;
  protected:
    using Event = SensorEvent;

    virtual void print(std::ostream& out) const{
      auto format=out.flags();
      out << "Sensor " << name() << " with id " << id() << " published to 0x" << std::hex << subject().value();
      out.setf(format);
    }

    void publish(const Event& e){
      pub.publish(e);
    }
    
  public:
    using Subject = famouso::mw::Subject;

    VREPSensor(simInt id, const Subject& subject)
      : VREPObject(id), pub(subject){
      pub.announce();
    }

    VREPSensor(const VREPSensor& copy)
      : VREPObject(copy), pub(copy.subject()){
      pub.announce();
    }

    virtual ~VREPSensor(){}

    const Subject& subject() const { return pub.subject(); }
};
