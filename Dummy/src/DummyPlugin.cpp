#include <VREPPlugin.h>
#include <Log.h>

class DummyPlugin: public VREPPlugin {
  public:
    DummyPlugin() {}
    DummyPlugin& operator=(const DummyPlugin&) = delete;
    DummyPlugin(const DummyPlugin&) = delete;
    virtual ~DummyPlugin() {}
    virtual unsigned char version() const { return 1; }
    virtual bool load() {
      Log::name(name());
      Log::out() << "loaded" << std::endl;
      return true;
    }
    virtual bool unload() {

      Log::out() << "unloaded" << std::endl;
      return true;
    }
    virtual const std::string name() const { 
      return "Dummy Plugin"; 
    }
} plugin;
