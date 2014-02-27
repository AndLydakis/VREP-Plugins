#pragma once

#include <VREPActuator.h>

class VelocityMotor : public VREPActuator{
  private:
    float buffer = 0.0f;
  protected:
    virtual void print(std::ostream& o);
    virtual void callback(const Event& e);
  public:
    VelocityMotor(simInt id, const Subject& subject);
    VelocityMotor(const VelocityMotor& copy);
    ~VelocityMotor();
    virtual void update();
};
