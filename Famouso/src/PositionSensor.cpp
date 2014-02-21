#include <PositionSensor.h>

#include <Log.h>
#include <mw/common/Event.h>

PositionSensor::PositionSensor(const PositionSensor& copy) : VREPSensor(copy){
}

PositionSensor::PositionSensor(simInt id, const famouso::mw::Subject& subject) 
  : VREPSensor(id, subject){
}

void PositionSensor::update(){
    float position[3];
    int res=simGetObjectPosition(id(), -1, position);
    if(res!=-1)
    {
      famouso::mw::Event e(subject());
      float temp[3];
      for(unsigned int j=0;j<3;j++)
        temp[j]=position[j];
      e.data=reinterpret_cast<uint8_t*>(temp);
      e.length=sizeof(temp);
      publish(e);
    }
    if(res==-1)
      Log::err() << "Error publishing position" << std::endl;
}

void PositionSensor::print(std::ostream& out) const{
  out << "Position ";
  VREPSensor::print(out);
}
