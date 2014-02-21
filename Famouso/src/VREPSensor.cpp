#include <VREPSensor.h>
#include <algorithm>

using std::move;

VREPSensor::VREPSensor(simInt id, const famouso::mw::Subject& subject) 
  : config::Famouso::Publisher(subject), mId(id) 
{
  announce();
}

VREPSensor::VREPSensor(const VREPSensor& copy) : config::Famouso::Publisher(copy.subject()), mId(copy.mId){
  announce();
}

std::ostream& operator<<(std::ostream& out, const VREPSensor& sensor){
  auto format=out.flags();
  out << "Sensor " << sensor.name() << " with id " << sensor.id() << " published to 0x" << std::hex << sensor.subject().value();
  out.setf(format);
  return out;
}
