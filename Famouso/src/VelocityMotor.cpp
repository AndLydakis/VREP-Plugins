#include <VelocityMotor.h>

#include <Log.h>

void VelocityMotor::print(std::ostream& o){
  o << "Velocity ";
  VREPActuator::print(o);
}

void VelocityMotor::callback(const Event& e){
  if(e.length==sizeof(float))
    buffer=*reinterpret_cast<float*>(e.data);
  else
    Log::err() << "Error parsing the data in " << *this;
}

VelocityMotor::VelocityMotor(simInt id, const Subject& subject) : VREPActuator(id, subject){
}

VelocityMotor::VelocityMotor(const VelocityMotor& copy) : VREPActuator(copy){

}

VelocityMotor::~VelocityMotor(){
  simSetJointTargetVelocity(mId, 0.0f);
}

void VelocityMotor::update(){
  simSetJointTargetVelocity(mId, buffer);
}
