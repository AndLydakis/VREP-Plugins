#include <VREPSensor.h>

VREPSensor::VREPSensor(simInt id, const Subject& subject) 
  : VREPObject(id), pub(subject){
  pub.announce();
}

VREPSensor::VREPSensor(const VREPSensor& copy) : VREPObject(copy), pub(copy.subject()){
  pub.announce();
}

VREPSensor::~VREPSensor(){
}

const VREPSensor::Subject& VREPSensor::subject() const {
  return pub.subject();
}

void VREPSensor::publish(const Event& e){
  pub.publish(e);
}

void VREPSensor::print(std::ostream& out) const{
  auto format=out.flags();
  out << "Sensor " << name() << " with id " << id() << " published to 0x" << std::hex << subject().value();
  out.setf(format);
}
