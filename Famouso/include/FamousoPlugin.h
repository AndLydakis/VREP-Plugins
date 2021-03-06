#pragma once

#include <VREPPlugin.h>
#include <VREPSensor.h>
#include <VREPActuator.h>


#include <string>
#include <map>
#include <memory>

#include <config.h>
#include <famouso.h>
#include <v_repLib.h>


class FamousoPlugin : public VREPPlugin, private config::Famouso{
  private:
    enum class MotorType
    {
      velocity,
      position
    };

    struct LaserData
    {
      std::shared_ptr<Subscriber> sub;
      int objectID;
      int obstackleID;
      float x;
      float y;
      float angle;
      float distance;
    };

    std::vector<std::unique_ptr<VREPObject>> mSensors;
    std::vector<std::unique_ptr<VREPActuator>> mActuators;
    std::map<famouso::mw::Subject, LaserData> laserSubs;

    void laserCallBack(famouso::mw::api::SECCallBackData& e);
   
  public:
    FamousoPlugin(){}
    virtual ~FamousoPlugin(){}
    FamousoPlugin& operator=(const FamousoPlugin&) = delete;
    virtual unsigned char version() const {return 2;}
    virtual const std::string name() const {return "Famouso Plugin";}
    virtual bool load();
    virtual void* action(int* auxiliaryData,void* customData,int* replyData);
    virtual void* close(int* auxiliaryData,void* customData,int* replyData);

    static void simExtPublishProximityData(SLuaCallBack* p);
    static void simExtPublishObjectPosition(SLuaCallBack* p);
    static void simExtSubscribeMotorVelocity(SLuaCallBack* p);
    static void simExtSubscribeMotorPosition(SLuaCallBack* p);
    static void simExtSubscribeLaserData(SLuaCallBack* p);
};
