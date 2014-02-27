#pragma once

#include <config.h>
#include <VREPObject.h>

class VREPActuator : public VREPObject{
  private:
    config::Famouso::Subscriber sub;
    void init();
    void trampoline(const famouso::mw::api::SECCallBackData& e);
  protected:
    typedef famouso::mw::api::SECCallBackData Event;
    virtual void print(std::ostream& out) const;
    virtual void callback(const Event& e) = 0;
  public:
    typedef famouso::mw::Subject Subject;
    VREPActuator(simInt id, const Subject& subject);
    VREPActuator(const VREPActuator& copy);
    virtual ~VREPActuator();
    const famouso::mw::Subject& subject() const;
};
