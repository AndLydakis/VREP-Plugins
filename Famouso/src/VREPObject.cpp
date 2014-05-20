#include <VREPObject.h>

VREPObject::VREPObject(simInt id) : mId(id){
}

VREPObject::VREPObject(const VREPObject& copy) : mId(copy.mId){
}

VREPObject::~VREPObject(){
}

simInt VREPObject::id() const {
  return mId;
}

std::string VREPObject::name() const{
  return simGetObjectName(mId);
}

simInt VREPObject::parent() const{
  return simGetObjectParent(mId);
}

bool VREPObject::operator==(const VREPObject& b){
  return mId==b.mId;
}

std::ostream& operator<<(std::ostream& out, const VREPObject& object){
  object.print(out);
  return out;
}
