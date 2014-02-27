#pragma once

#include <VREPActuator.h>

class PositionMotor : public VREPActuator{
  private:
    float buffer = 0.0f;
  protected:
    virtual void print(std::ostream& o);
    virtual void callback(const Event& e);
  public:
    PositionMotor(simInt id, const Subject& subject);
    PositionMotor(const PositionMotor& copy);
    ~PositionMotor();
    virtual void update();
};
