#pragma once

#include <VREPSensor.h>
#include <atomic>

class ProximitySensor : public VREPSensor{
  private:
    std::atomic<float> mRange;
    bool mPeriodic;
  protected:
    void print(std::ostream& out) const;
  public:
    ProximitySensor(const ProximitySensor& copy);
    ProximitySensor& operator=(const ProximitySensor&) = delete;
    ProximitySensor(simInt id, const famouso::mw::Subject& subject,
                    bool periodic=false, float range=0.0);
    virtual void update();
    bool isPeriodic() const   {return mPeriodic;}
    float range() const     {return mRange.load();}
    void range(float value) {mRange=value;}
};
