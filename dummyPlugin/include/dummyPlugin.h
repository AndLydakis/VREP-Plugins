#pragma once

#include <vrepPlugin.h>
#include <pluginLog.h>

class DummyPlugin: public VRepPlugin
{
    protected:
        PluginLog log;
    public:
        DummyPlugin();
        virtual ~DummyPlugin();
        virtual unsigned char version() const;
        virtual bool load();
        virtual bool unload();
        virtual const std::string name() const;
};
