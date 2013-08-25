#include <pluginLog.h>

PluginLog::PluginLog(VRepPlugin& plugin, std::ostream& baseStream) : 
    plugin(plugin),
    baseStream(baseStream)
{

}

PluginLog::~PluginLog()
{

}
