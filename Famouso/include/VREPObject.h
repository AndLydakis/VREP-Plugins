#pragma once

#include <v_repLib.h>

#include <string>
#include <ostream>

class VREPObject{
  protected:
    const simInt mId;

  protected:
    virtual void print(std::ostream& out) const = 0;

  public:
    VREPObject(simInt id);
    VREPObject(const VREPObject& copy);
    VREPObject& operator=(const VREPObject& copy) = delete;
    virtual ~VREPObject();
    bool operator==(const VREPObject& b);
    simInt id() const;
    std::string name() const;
    virtual void update() = 0;

  friend std::ostream& operator<<(std::ostream&, const VREPObject&);
};

std::ostream& operator<<(std::ostream& out, const VREPObject& object);
