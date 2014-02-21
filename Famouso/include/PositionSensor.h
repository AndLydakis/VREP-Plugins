#pragma once

#include <VREPSensor.h>

class PositionSensor : public VREPSensor{
  protected:
    void print(std::ostream& out) const;
  public:
    PositionSensor(const PositionSensor& copy);
    PositionSensor& operator=(const PositionSensor&) = delete;
    PositionSensor(simInt id, const famouso::mw::Subject& subject);
    virtual void update();
};
