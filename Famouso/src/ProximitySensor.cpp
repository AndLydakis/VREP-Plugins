#include <ProximitySensor.h>

#include <Log.h>
#include <mw/common/Event.h>

void ProximitySensor::update()
{
  float buffer[4];
  simInt res;
  Event e;

  buffer[0] = simGetSimulationTime();
  if(buffer[0]<0)
    Log::err() << "Error publishing distance: no time" << std::endl;
  else
    e.attribute(id::attribute::Time()).value()={{buffer[0]}};

  e.attribute(id::attribute::Reference()).value() = {{ parent() }};
  e.attribute(id::attribute::PublisherID()).value()   = {{ (unsigned int)id() }};
  e.attribute(id::attribute::Validity()).value()      = {{ 1.0f }};

  if(simGetObjectPosition(id(), parent(), buffer)==-1)
    Log::err() << "Error publishing distance: no position" << std::endl;
  else
    e.attribute(id::attribute::Position()).value()    = {{ buffer[0] }, { buffer[1] } , { buffer[2] }};

  if(simGetObjectOrientation(id(), parent(), buffer)==-1)
    Log::err() << "Error publishing distance: no orientation" << std::endl;
  else
    e.attribute(id::attribute::Orientation()).value()    = {{ buffer[0] }, { buffer[1] } , { buffer[2] }};

  res=simReadProximitySensor(id(), buffer, NULL, NULL);
  switch(res){
    case(-1): Log::err() << "Error publishing distance: no distance" << std::endl;
              break;
    case(1):  e.attribute(id::attribute::Distance()).value()    ={{ buffer[3] }};
              e.attribute(id::attribute::Angle()).value()  = {{ asinf(buffer[0]/buffer[3]) }, { asinf(buffer[1]/buffer[3]) }};
              e.attribute(id::attribute::Angle()).value()*=180/M_PI;
              this->publish(e);
              break;
  }
}

void ProximitySensor::print(std::ostream& out) const{
  out << "Proximity ";
  VREPSensor::print(out);
}
