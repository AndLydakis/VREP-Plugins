#include "dummyPlugin.h"

#include <iostream>

DummyPlugin::DummyPlugin() : log(*this, std::cout)
{
    
}

DummyPlugin::~DummyPlugin()
{

}

unsigned char DummyPlugin::version() const
{
    return 1;
}

const std::string DummyPlugin::name() const
{
    return "Dummy Plugin";
}

bool DummyPlugin::load()
{
    log << "loaded" << std::endl;
    return true;
}

bool DummyPlugin::unload()
{
    log << "unloaded" << std::endl;
    return true;
}

DummyPlugin plugin;
