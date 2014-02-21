#include <VREPPlugin.h>
#include <iostream>

VRepPlugin& VRepPlugin::getInstance()
{
    if(!instance)
        std::cout << "No plugin registered!" << std::endl;
    return *instance;
}

VRepPlugin::VRepPlugin()
{
    instance=this;
}

VRepPlugin::~VRepPlugin()
{
    instance=NULL;
}

bool VRepPlugin::load()
{
    return true;
}

bool VRepPlugin::unload()
{
    return true;
}

void* VRepPlugin::refreshDialog(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::menuItemSelected(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::sceneContentChange(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::instancePass(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::instanceSwitch(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::mainScriptCall(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::simStart(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::simEnd(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::open(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::action(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::close(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::save(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::render(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::broadcast(int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

void* VRepPlugin::handleOtherMessage(int message, int* auxiliaryData,void* customData,int* replyData)
{
    return NULL;
}

VRepPlugin* VRepPlugin::instance;
