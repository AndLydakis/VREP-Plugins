#include <PositionMotor.h>

#include <Log.h>

void PositionMotor::print(std::ostream& o){
  o << "Position ";
  VREPActuator::print(o);
}

void PositionMotor::callback(const Event& e){
  if(e.length==sizeof(float))
    buffer=*reinterpret_cast<float*>(e.data);
  else
    Log::err() << "Error parsing the data in " << *this;
}

PositionMotor::PositionMotor(simInt id, const Subject& subject) : VREPActuator(id, subject){
}

PositionMotor::PositionMotor(const PositionMotor& copy) : VREPActuator(copy){

}

PositionMotor::~PositionMotor(){
  simSetJointTargetPosition(mId, 0.0f);
}

void PositionMotor::update(){
  simSetJointTargetPosition(mId, buffer);
}
