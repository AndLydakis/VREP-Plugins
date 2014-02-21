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

void VREPSensor::print(std::ostream& out) const{
  auto format=out.flags();
  out << "Sensor " << name() << " with id " << id() << " published to 0x" << std::hex << subject().value();
  out.setf(format);
}

std::ostream& operator<<(std::ostream& out, const VREPSensor& sensor){
  sensor.print(out);
  return out;
}
