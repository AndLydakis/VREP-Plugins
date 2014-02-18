#include <ProximitySensor.h>
#include <mw/common/Event.h>

void ProximitySensor::update()
{
  float distanceParameter[4];
  simInt res=simReadProximitySensor(id(), distanceParameter, NULL, NULL);
  float temp=range();
  switch(res){
    case(1):  temp=distanceParameter[3];
              break;
    case(-1): //errorLog << "Error publishing distance" << std::endl;
              return;
  }
  if(!isPeriodic())
    return;
  famouso::mw::Event e(subject());
  e.data=reinterpret_cast<uint8_t*>(&temp);
  e.length=sizeof(temp);
  publish(e);
}

std::ostream& operator<<(std::ostream& out, const ProximitySensor& sensor){
  out << "Proximity" << static_cast<const VREPSensor&>(sensor);
  if(sensor.isPeriodic())
    out << " periodically with max range " << sensor.range();
  else
    out << " aperiodically";
  return out;
}
