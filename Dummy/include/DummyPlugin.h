#pragma once

#include <VREPPlugin.h>

class DummyPlugin: public VREPPlugin
{
    public:
        DummyPlugin(){}
        DummyPlugin& operator=(const DummyPlugin&) = delete;
        DummyPlugin(const DummyPlugin&) = delete;
        virtual ~DummyPlugin(){}
        virtual unsigned char version() const;
        virtual bool load();
        virtual bool unload();
        virtual const std::string name() const;
};
