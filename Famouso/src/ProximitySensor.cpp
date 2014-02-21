#include <ProximitySensor.h>

#include <Log.h>
#include <mw/common/Event.h>

ProximitySensor::ProximitySensor(simInt id, const famouso::mw::Subject& subject, 
                                 bool periodic, float range)
  : VREPSensor(id, subject), mRange(range), mPeriodic(periodic)
{}

ProximitySensor::ProximitySensor(const ProximitySensor& copy) 
  : VREPSensor(copy), mRange(copy.mRange.load()), mPeriodic(copy.mPeriodic)
{}

void ProximitySensor::update()
{
  float distanceParameter[4];
  simInt res=simReadProximitySensor(id(), distanceParameter, NULL, NULL);
  float temp=range();
  switch(res){
    case(1):  temp=distanceParameter[3];
              break;
    case(-1): Log::err() << "Error publishing distance" << std::endl;
              return;
  }
  if(!isPeriodic())
    return;
  famouso::mw::Event e(subject());
  e.data=reinterpret_cast<uint8_t*>(&temp);
  e.length=sizeof(temp);
  publish(e);
}

void ProximitySensor::print(std::ostream& out) const{
  out << "Proximity ";
  VREPSensor::print(out);
  if(isPeriodic())
    out << " periodically with max range " << range() << "m";
  else
    out << " aperiodically";
}
