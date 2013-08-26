#pragma once

#include <vrepPlugin.h>
#include <pluginLog.h>

#include <string>
#include <map>

#include <mw/el/EventLayerClientStub.h>
#include <mw/api/PublisherEventChannel.h>
#include <mw/api/SubscriberEventChannel.h>
#include <famouso.h>

class FamousoPlugin : public VRepPlugin
{
  private:
    static constexpr const char* noseTopic="Nose    ";
    static constexpr const char* lMotorTopic="LMotor  ";
    static constexpr const char* rMotorTopic="RMotor  ";

    struct config
    {
      typedef famouso::mw::el::EventLayerClientStub EL;
      typedef famouso::mw::api::PublisherEventChannel< EL > PEC;
      typedef famouso::mw::api::SubscriberEventChannel< EL > SEC;
    };

    typedef config::PEC Publisher;
    typedef config::SEC Subscriber;

    enum Motors
    {
      left,
      right
    };

    std::map<std::string, int> objects;
    float velocityBuffer[2];
    Publisher* nosePubPtr;
    Subscriber* lMotorSubPtr;
    Subscriber* rMotorSubPtr;

    bool initialized;

    void handleEvent(famouso::mw::api::SECCallBackData& cbd);

  protected:
    PluginLog log;
    PluginLog errorLog;
    
  public:
    FamousoPlugin();
    virtual unsigned char version() const {return 1;}
    virtual const std::string name() const {return "Famouso Plugin";}
    virtual bool load();
    virtual void* open(int* auxiliaryData,void* customData,int* replyData);
    virtual void* action(int* auxiliaryData,void* customData,int* replyData);
    virtual void* close(int* auxiliaryData,void* customData,int* replyData);
};
