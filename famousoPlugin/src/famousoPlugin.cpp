#include <iostream>
#include <list>

#include "famousoPlugin.h"

#include <v_repLib.h>

FamousoPlugin::FamousoPlugin() : velocityBuffer{0.0f,0.0f}, initialized(false), log(*this, std::cerr), 
                                 errorLog(*this, std::cerr)
{}

bool FamousoPlugin::load()
{
    famouso::init<config>();

  return true;
}

void FamousoPlugin::handleEvent(famouso::mw::api::SECCallBackData& cbd)
{
  if(cbd.length>=sizeof(float))
    if(cbd.subject==lMotorSubPtr->subject())
      velocityBuffer[left]=*reinterpret_cast<float*>(cbd.data);
    if(cbd.subject==rMotorSubPtr->subject())
      velocityBuffer[right]=*reinterpret_cast<float*>(cbd.data);
}

void* FamousoPlugin::open(int* auxiliaryData,void* customData,int* replyData)
{
  log << "opened" << std::endl;
  objects.clear();
  int robot=simGetObjectHandle((std::string("Bubble_Robot")+"#").c_str());
  if(robot==-1)
  {
    errorLog << "initialization failed: Bubble_Robot not found!" << std::endl;
    return NULL;
  }
   
  std::list<int> parents;
  parents.push_back(robot);
  for(auto i: parents)
  {
    const char* name=simGetObjectName(i);
    if(!name)
    {
      errorLog << "name lookup of handle " << i << " failed!" << std::endl;
      break;
    }

    objects[name]=i;
    for(int child=0;;child++)
    {
      int childHandle=simGetObjectChild(i,child);
      if(childHandle!=-1)
        parents.push_back(childHandle);
      else
        break;
    }    
  }
  log << "retrieved objects:" << std::endl;
  for(auto i : objects)
    log << "\t" << i.first << ": " << i.second << std::endl;
  log << "binding topics" << std::endl;
  nosePubPtr=new Publisher(noseTopic);
  if(!nosePubPtr)
  {
    errorLog << "error creating nose publisher" << std::endl;
    return NULL;
  }
  nosePubPtr->announce();
  lMotorSubPtr=new Subscriber(lMotorTopic);
  if(!lMotorSubPtr)
  {
    errorLog << "error creating left motor subscriber" << std::endl;
    return NULL;
  }
  lMotorSubPtr->subscribe();
  lMotorSubPtr->callback.bind<FamousoPlugin, &FamousoPlugin::handleEvent>(this);
  rMotorSubPtr=new Subscriber(rMotorTopic);
  if(!rMotorSubPtr)
  {
    errorLog << "error creating right motor subscriber" << std::endl;
    return NULL;
  }
  rMotorSubPtr->subscribe();
  rMotorSubPtr->callback.bind<FamousoPlugin, &FamousoPlugin::handleEvent>(this);
  initialized=true;
  return NULL;
}

void* FamousoPlugin::action(int* auxiliaryData,void* customData,int* replyData)
{
  if(initialized)
  {
    float distanceParameter[4];
    if(simReadProximitySensor(objects["Nose"], distanceParameter, NULL, NULL))
    {
      famouso::mw::Event e(nosePubPtr->subject());
      e.data=reinterpret_cast<uint8_t*>(&distanceParameter[3]);
      e.length=sizeof(float);
      nosePubPtr->publish(e);
    }

    simSetJointTargetVelocity(objects["Left_Motor"], velocityBuffer[left]);
    simSetJointTargetVelocity(objects["Right_Motor"], velocityBuffer[right]);
  }
  return NULL;
}

void* FamousoPlugin::close(int* auxiliaryData,void* customData,int* replyData)
{
  if(initialized)
  {
    delete nosePubPtr;
    nosePubPtr=NULL;
    delete lMotorSubPtr;
    lMotorSubPtr=NULL;
    delete rMotorSubPtr;
    rMotorSubPtr=NULL;
  }
  initialized=false;
  objects.clear();
  log << "closed" << std::endl;
  return NULL;
}

FamousoPlugin plugin;
