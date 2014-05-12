#pragma once

#include <VREPSensor.h>

#include <BaseEvent.h>
#include <Serializer.h>

#include <atomic>

using DistanceAttribute = Attribute<id::attribute::Distance, Value<float, 1, false>, boost::units::si::length>;
using DistanceSensorEvent = typename BaseEvent<>::append<DistanceAttribute>::type;

class ProximitySensor : public VREPSensor<DistanceSensorEvent>{
  private:
    std::atomic<float> mRange;
    bool mPeriodic;
    using Base =  VREPSensor<DistanceSensorEvent>;

  protected:
    void print(std::ostream& out) const;

  public:
    using Event = typename Base::Event;

    ProximitySensor(const ProximitySensor& copy);
    ProximitySensor& operator=(const ProximitySensor&) = delete;
    ProximitySensor(simInt id, const famouso::mw::Subject& subject,
                    bool periodic=false, float range=0.0);
    virtual void update();
    bool isPeriodic() const   {return mPeriodic;}
    float range() const     {return mRange.load();}
    void range(float value) {mRange=value;}
};
