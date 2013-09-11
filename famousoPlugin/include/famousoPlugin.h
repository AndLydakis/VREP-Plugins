#pragma once

#include <vrepPlugin.h>
#include <pluginLog.h>

#include <string>
#include <map>

#include <mw/el/EventLayerClientStub.h>
#include <mw/api/PublisherEventChannel.h>
#include <mw/api/SubscriberEventChannel.h>
#include <famouso.h>
#include <mw/common/ExtendedEvent.h>

#include <v_repLib.h>

class FamousoPlugin : public VRepPlugin
{
  private:
    struct config
    {
      typedef famouso::mw::el::EventLayerClientStub EL;
      typedef famouso::mw::api::PublisherEventChannel< EL > PEC;
      typedef famouso::mw::api::SubscriberEventChannel< EL > SEC;
    };

    typedef config::PEC Publisher;
    typedef config::SEC Subscriber;

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

    std::map<int, std::shared_ptr<Publisher>> proximityPubs;
    std::map<famouso::mw::Subject, MotorData> motorSubs;

    void motorCallBack(famouso::mw::api::SECCallBackData& e);

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
    static void simExtSubscribeMotorVelocity(SLuaCallBack* p);
    static void simExtSubscribeMotorPosition(SLuaCallBack* p);
};
