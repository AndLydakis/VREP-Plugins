#include <iostream>
#include <list>

#include "famousoPlugin.h"

FamousoPlugin plugin;

void FamousoPlugin::simExtPublishProximityData(SLuaCallBack* p)
{
  const char* proximityName=simGetObjectName(p->inputInt[0]);
  if(proximityName)
  {
    plugin.log << "registering proximity sensor " << proximityName
               << " for periodic publication to subject \"" << p->inputChar
               << "\" with publisher id " << p->inputInt[1] << std::endl;
    auto pub=std::shared_ptr<Publisher>(new Publisher(p->inputChar));
    plugin.proximityPubs[p->inputInt[0]]=pub;
    pub->announce();
  }
}

void FamousoPlugin::simExtSubscribeMotorVelocity(SLuaCallBack* p)
{
  const char* motorName=simGetObjectName(p->inputInt[0]);
  if(motorName)
  {
    plugin.log << "subscribing for velocity of motor " << motorName
               << " on subject \"" << p->inputChar
               << "\"" << std::endl;
    std::shared_ptr<Subscriber> sub(new Subscriber(p->inputChar));
    plugin.motorSubs[sub->subject()]={sub, p->inputInt[0], 0.0f, MotorType::velocity};
    sub->subscribe();
    sub->callback.bind<FamousoPlugin, &FamousoPlugin::motorCallBack>(&plugin);
  }
}

void FamousoPlugin::simExtSubscribeMotorPosition(SLuaCallBack* p)
{
  const char* motorName=simGetObjectName(p->inputInt[0]);
  if(motorName)
  {
    plugin.log << "subscribing for position of motor " << motorName
               << " on subject \"" << p->inputChar
               << "\"" << std::endl;
    std::shared_ptr<Subscriber> sub(new Subscriber(p->inputChar));
    plugin.motorSubs[sub->subject()]={sub, p->inputInt[0], 0.0f, MotorType::position};
    sub->subscribe();
    sub->callback.bind<FamousoPlugin, &FamousoPlugin::motorCallBack>(&plugin);
  }
}

void FamousoPlugin::motorCallBack(famouso::mw::api::SECCallBackData& e)
{
  if(e.length==sizeof(float))
    motorSubs[e.subject].buffer=*reinterpret_cast<float*>(e.data);
}

FamousoPlugin::FamousoPlugin() :  log(*this, std::cerr), errorLog(*this, std::cerr)
{}

bool FamousoPlugin::load()
{
  famouso::init<config>();

  int argType[4]={3, sim_lua_arg_int, sim_lua_arg_string, sim_lua_arg_int};
  if(simRegisterCustomLuaFunction("simExtFamousoPublishProximityData",
                                  "objectID of proximity sensor@subject of proximity data@id of publisher",
                                  argType,
                                  &FamousoPlugin::simExtPublishProximityData
                                  )==-1)
    errorLog << "Error registering custom lua function simExtFamousoPublishProximityData" << std::endl;

  argType[0]=2;
  argType[1]=sim_lua_arg_int;
  argType[2]=sim_lua_arg_string;
  if(simRegisterCustomLuaFunction("simExtFamousoSubscribeMotorVelocity",
                                  "objectID of motorized joint@subject of motor data",
                                  argType,
                                  &FamousoPlugin::simExtSubscribeMotorVelocity
                                  )==-1)
    errorLog << "Error registering custom lua function simExtFamousoSubscribeMotorVelocity" << std::endl;
  if(simRegisterCustomLuaFunction("simExtFamousoSubscribeMotorPosition",
                                  "objectID of motorized joint@subject of motor data",
                                  argType,
                                  &FamousoPlugin::simExtSubscribeMotorPosition
                                  )==-1)
    errorLog << "Error registering custom lua function simExtFamousoSubscribeMotorPosition" << std::endl;
  return true;
}

void* FamousoPlugin::action(int* auxiliaryData,void* customData,int* replyData)
{
  for(auto i : proximityPubs)
  {
    float distanceParameter[4];
    int res=simReadProximitySensor(i.first, distanceParameter, NULL, NULL);
    if(res==1)
    {
      famouso::mw::Event e(i.second->subject());
      e.data=reinterpret_cast<uint8_t*>(&distanceParameter[3]);
      e.length=sizeof(float);
      i.second->publish(e);
    }
    if(res==-1)
      errorLog << "Error publishing distance" << std::endl;
  }

  for(auto i : motorSubs)
  {
    switch(i.second.type)
    {
      case(MotorType::velocity):
        if(simSetJointTargetVelocity(i.second.objectID, i.second.buffer)==-1)
          errorLog << "Error setting target velocity for motor " << simGetObjectName(i.second.objectID) << std::endl;
        break;
      case(MotorType::position):
        if(simSetJointTargetPosition(i.second.objectID, i.second.buffer)==-1)
          errorLog << "Error setting target position for motor " << simGetObjectName(i.second.objectID) << std::endl;
        break;
    }
  }
  return NULL;
}

void* FamousoPlugin::close(int* auxiliaryData,void* customData,int* replyData)
{
  proximityPubs.clear();
  motorSubs.clear();
  log << "closed" << std::endl;
  return NULL;
}


