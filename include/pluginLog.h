#pragma once

#include "vrepPlugin.h"
#include <ostream>

class PluginLog
{
    private:
        VRepPlugin& plugin;
        std::ostream& baseStream;
    public:
        PluginLog(VRepPlugin& plugin, std::ostream& baseStream);
        virtual ~PluginLog();
        template<typename T>
        std::ostream& operator<<(const T& t)
        {
            return baseStream << "[" << plugin.name() << "]: " << t;
        }
};
