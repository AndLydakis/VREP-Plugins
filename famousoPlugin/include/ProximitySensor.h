#pragma once

#include <VREPSensor.h>
#include <atomic>

class ProximitySensor : public VREPSensor{
  private:
    std::atomic<float> mRange;
    bool mPeriodic;

  public:
    ProximitySensor(simInt id, const famouso::mw::Subject& subject,
                    bool periodic=false, float range=0.0) 
      : VREPSensor(id, subject), mRange(range), mPeriodic(periodic)
    {}
    ProximitySensor(const ProximitySensor&&);
    virtual void update();
    bool isPeriodic() const   {return mPeriodic;}
    float range() const     {return mRange.load();}
    void range(float value) {mRange=value;}
};

std::ostream& operator<<(std::ostream& out, const ProximitySensor& sensor);
