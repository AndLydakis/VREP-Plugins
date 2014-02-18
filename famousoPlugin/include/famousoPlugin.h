#pragma once

#include <vrepPlugin.h>
#include <pluginLog.h>

#include <string>
#include <map>

#include <config.h>
#include <famouso.h>
#include <v_repLib.h>
#include <ProximitySensor.h>

class FamousoPlugin : public VRepPlugin, private config::Famouso{
  private:
    enum class MotorType
    {
      velocity,
      position
    };

    struct MotorData
    {
      std::shared_ptr<Subscriber> sub;
      int objectID;
      float buffer;
      MotorType type;
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

/*    struct ProximityData
    {
      std::shared_ptr<Publisher> pub;
      int objectID;
      bool periodic;
      float defaultValue;
    };*/

    struct PositionData
    {
      std::shared_ptr<Publisher> pub;
      int objectID;
    };

    std::vector<ProximitySensor> proximitySensors;
    std::vector<PositionData> positionPubs;
    std::map<famouso::mw::Subject, MotorData> motorSubs;
    std::map<famouso::mw::Subject, LaserData> laserSubs;

    void motorCallBack(famouso::mw::api::SECCallBackData& e);
    void laserCallBack(famouso::mw::api::SECCallBackData& e);

  protected:
    PluginLog log;
    PluginLog errorLog;
    
  public:
    FamousoPlugin();
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
