#include <FamousoPlugin.h>

#include <ProximitySensor.h>
#include <PositionSensor.h>
#include <Log.h>

#include <list>
#include <algorithm>

FamousoPlugin plugin;

void FamousoPlugin::simExtPublishProximityData(SLuaCallBack* p)
{
  const char* sensorName=simGetObjectName(p->inputInt[0]);
  if(sensorName)
  {
    const char* sensorTopic  = p->inputChar;
    simInt      sensorObject = p->inputInt[0];
    simBool     isPeriodic   = p->inputBool[0];
    simFloat    sensorRange  = p->inputFloat[0];
    
    plugin.mSensors.emplace_back(new ProximitySensor(sensorObject, sensorTopic, isPeriodic, sensorRange));

    Log::out() << "Registering " << *plugin.mSensors.back() << std::endl;
  }
}

void FamousoPlugin::simExtPublishObjectPosition(SLuaCallBack* p)
{
  const char* sensorName=simGetObjectName(p->inputInt[0]);
  if(sensorName)
  {
    const char* sensorTopic  = p->inputChar;
    simInt      sensorObject = p->inputInt[0];
    
    plugin.mSensors.emplace_back(new PositionSensor(sensorObject, sensorTopic));

    Log::out() << "Registering " << *plugin.mSensors.back() << std::endl;
  }
}

void FamousoPlugin::simExtSubscribeMotorVelocity(SLuaCallBack* p)
{
  const char* motorName=simGetObjectName(p->inputInt[0]);
  if(motorName)
  {
    Log::out() << "subscribing for velocity of motor " << motorName
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
    Log::out() << "subscribing for position of motor " << motorName
               << " on subject \"" << p->inputChar
               << "\"" << std::endl;
    std::shared_ptr<Subscriber> sub(new Subscriber(p->inputChar));
    plugin.motorSubs[sub->subject()]={sub, p->inputInt[0], 0.0f, MotorType::position};
    sub->subscribe();
    sub->callback.bind<FamousoPlugin, &FamousoPlugin::motorCallBack>(&plugin);
  }
}

void FamousoPlugin::simExtSubscribeLaserData(SLuaCallBack* p)
{
  const char* obstackleName=simGetObjectName(p->inputInt[0]);
  if(obstackleName)
  {
    Log::out() << "subscribing for laser scanner data of " << simGetObjectName(p->objectID) << " detecting " << obstackleName
               << " on subject \"" << p->inputChar << "\"" << std::endl;
    std::shared_ptr<Subscriber> sub(new Subscriber(p->inputChar));
    plugin.laserSubs[sub->subject()]={sub, p->objectID, p->inputInt[0], 0.0f, 0.0f};
    sub->subscribe();
    sub->callback.bind<FamousoPlugin, &FamousoPlugin::laserCallBack>(&plugin);
  }
}

void FamousoPlugin::motorCallBack(famouso::mw::api::SECCallBackData& e)
{
  if(e.length==sizeof(float))
    motorSubs[e.subject].buffer=*reinterpret_cast<float*>(e.data);
}

void FamousoPlugin::laserCallBack(famouso::mw::api::SECCallBackData& e)
{
  if(e.length>=4*sizeof(float))
  {
    float* data=reinterpret_cast<float*>(e.data);
    laserSubs[e.subject].x=data[0];
    laserSubs[e.subject].y=data[1];
    laserSubs[e.subject].angle=data[2];
    laserSubs[e.subject].distance=data[3];
  }
}

bool FamousoPlugin::load()
{
  Log::name(name());
  famouso::init<config::Famouso>();

  int argType[5]={4, sim_lua_arg_int, sim_lua_arg_string, sim_lua_arg_bool, sim_lua_arg_float};
  if(simRegisterCustomLuaFunction("simExtFamousoPublishProximityData",
                                  "objectID of proximity sensor@subject of proximity data@periodic@default value",
                                  argType,
                                  &FamousoPlugin::simExtPublishProximityData
                                  )==-1)
    Log::err() << "Error registering custom lua function simExtFamousoPublishProximityData" << std::endl;
  argType[0]=2;
  argType[1]=sim_lua_arg_int;
  argType[2]=sim_lua_arg_string;
  if(simRegisterCustomLuaFunction("simExtFamousoPublishObjectPosition",
                                  "objectID@subject of position data",
                                  argType,
                                  &FamousoPlugin::simExtPublishObjectPosition
                                  )==-1)
    Log::err() << "Error registering custom lua function simExtFamousoPublishObjectPosition" << std::endl;
  if(simRegisterCustomLuaFunction("simExtFamousoSubscribeMotorVelocity",
                                  "objectID of motorized joint@subject of motor data",
                                  argType,
                                  &FamousoPlugin::simExtSubscribeMotorVelocity
                                  )==-1)
    Log::err() << "Error registering custom lua function simExtFamousoSubscribeMotorVelocity" << std::endl;
  if(simRegisterCustomLuaFunction("simExtFamousoSubscribeMotorPosition",
                                  "objectID of motorized joint@subject of motor data",
                                  argType,
                                  &FamousoPlugin::simExtSubscribeMotorPosition
                                  )==-1)
    Log::err() << "Error registering custom lua function simExtFamousoSubscribeMotorPosition" << std::endl;
  if(simRegisterCustomLuaFunction("simExtFamousoSubscribeLaserData",
                                  "objectID of obstackle@subject of laser data",
                                  argType,
                                  &FamousoPlugin::simExtSubscribeLaserData
                                  )==-1)
    Log::err() << "Error registering custom lua function simExtFamousoSubscribeLaserData" << std::endl;
  return true;
}

void* FamousoPlugin::action(int* auxiliaryData,void* customData,int* replyData)
{
  for(auto sensor : mSensors)
    sensor->update();

  for(auto i : motorSubs)
  {
    switch(i.second.type)
    {
      case(MotorType::velocity):
        if(simSetJointTargetVelocity(i.second.objectID, i.second.buffer)==-1)
          Log::err() << "Error setting target velocity for motor " << simGetObjectName(i.second.objectID) << std::endl;
        break;
      case(MotorType::position):
        if(simSetJointTargetPosition(i.second.objectID, i.second.buffer)==-1)
          Log::err() << "Error setting target position for motor " << simGetObjectName(i.second.objectID) << std::endl;
        break;
    }
  }

  for(auto i : laserSubs)
  {
    simInt prop=simGetObjectSpecialProperty(i.second.obstackleID);
    if(prop==-1)
      Log::err() << "Error getting obstackle special property" << std::endl;
    if(i.second.distance>0.0f)
      prop|=sim_objectspecialproperty_collidable;
    else
      prop&=~sim_objectspecialproperty_collidable;
    if(simSetObjectProperty(i.second.obstackleID, prop)==-1)
      Log::err() << "Error setting obstackle special property" << std::endl;
    float position[3]={i.second.y, 0.0f, i.second.x};
    if(simSetObjectPosition(i.second.obstackleID, i.second.objectID, position)==-1)
      Log::err() << "Error moving obstackle" << std::endl;
  }
  return NULL;
}

void* FamousoPlugin::close(int* auxiliaryData,void* customData,int* replyData)
{
  mSensors.clear();
  motorSubs.clear();
  laserSubs.clear();
  Log::out() << "closed" << std::endl;
  return NULL;
}
