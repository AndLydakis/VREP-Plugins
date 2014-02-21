#pragma once

#include <mw/el/EventLayerClientStub.h>
#include <mw/api/PublisherEventChannel.h>
#include <mw/api/SubscriberEventChannel.h>

namespace config{
  struct Famouso{
    typedef ::famouso::mw::el::EventLayerClientStub EL;
    typedef ::famouso::mw::api::PublisherEventChannel< EL > Publisher;
    typedef ::famouso::mw::api::SubscriberEventChannel< EL > Subscriber;
  };
};
