//
// Created by Administrator on 2025/7/27.
//

#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H
#include "../ThirdParty.h"
namespace FCT
{
    namespace EventSystemConfig
    {
        struct QueueOnly {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = false;
        };
        struct TriggerOnly {
            static constexpr bool EnableQueue = false;
            static constexpr bool EnableTrigger = true;
        };
        struct Full {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = true;
        };
    }
    using SubscribeId = entt::connection;
    template<typename Config = EventSystemConfig::Full>
    class IEventSystem {
    protected:
        entt::dispatcher m_dispatcher;
    public:
        template<typename Event>
        void trigger(const Event& event)
            requires Config::EnableTrigger
        {
            m_dispatcher.trigger(event);
        }

        template<typename Event>
        void enqueue(const Event& event)
            requires Config::EnableQueue
        {
            m_dispatcher.enqueue(event);
        }

        template<typename Event>
        void update()
            requires Config::EnableQueue
        {
            m_dispatcher.update<Event>();
        }

        void updateAll()
            requires Config::EnableQueue
        {
            m_dispatcher.update();
        }

        template<typename Event, typename Func>
        SubscribeId subscribe(Func&& func) {
            return m_dispatcher.sink<Event>().connect(std::forward<Func>(func));
        }

        template<typename Event>
        void unsubscribe(SubscribeId& conn) {
            m_dispatcher.sink<Event>().disconnect(conn);
        }

        template<typename Event>
        void unsubscribeAll() {
            m_dispatcher.sink<Event>().disconnect();
        }
	};
}
#endif //EVENTSYSTEM_H
