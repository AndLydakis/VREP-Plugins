#include <VREPActuator.h>

void VREPActuator::print(std::ostream& out) const{
  auto format=out.flags();
  out << "Actuator " << name() << " with id " << id() << " subscribed to 0x" << std::hex << subject().value();
  out.setf(format);
}

void VREPActuator::trampoline(const Event& e){
  callback(e);
}

void VREPActuator::init(){
  sub.subscribe();
  sub.callback.bind<VREPActuator, &VREPActuator::trampoline>(this);
}

VREPActuator::VREPActuator(simInt id, const famouso::mw::Subject& subject) : VREPObject(id), sub(subject){
  init();
}

VREPActuator::VREPActuator(const VREPActuator& copy) : VREPObject(copy), sub(copy.subject()){
  init();
}

VREPActuator::~VREPActuator(){
}

const famouso::mw::Subject& VREPActuator::subject() const{
  return sub.subject();
}
