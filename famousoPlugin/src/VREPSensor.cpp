#include <VREPSensor.h>

std::ostream& operator<<(std::ostream& out, const VREPSensor& sensor){
  out << "Sensor " << sensor.name() << " with id " << sensor.id() << " published to " << sensor.subject();
  return out;
}
