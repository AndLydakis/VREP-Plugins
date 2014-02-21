#pragma once

#include <VREPPlugin.h>

class DummyPlugin: public VRepPlugin
{
    public:
        DummyPlugin();
        virtual ~DummyPlugin();
        virtual unsigned char version() const;
        virtual bool load();
        virtual bool unload();
        virtual const std::string name() const;
};
