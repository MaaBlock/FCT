//
// Created by Administrator on 2025/7/27.
//

#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H
#include "../ThirdParty.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

namespace FCT
{
    namespace EventSystemConfig
    {
        struct QueueOnly {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = false;
            static constexpr bool EventAsData = true;
        };
        struct TriggerOnly {
            static constexpr bool EnableQueue = false;
            static constexpr bool EnableTrigger = true;
            static constexpr bool EventAsData = true;
        };
        struct Full {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = true;
            static constexpr bool EventAsData = true;
        };
        struct IdentifierFull {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = true;
            static constexpr bool EventAsData = false;
        };
        struct IdentifierTriggerOnly {
            static constexpr bool EnableQueue = true;
            static constexpr bool EnableTrigger = true;
            static constexpr bool EventAsData = false;
        };
    }
    using SubscribeId = std::size_t;

    template<typename Config = EventSystemConfig::Full>
    class IEventSystem {
    private:
        template<typename Event>
        static constexpr auto getEventTypeId() {
            return entt::type_hash<Event>::value();
        }

        struct IEventHandler {
            virtual ~IEventHandler() = default;
            virtual void handle(const void* event) = 0;
        };

        template<typename Event>
        struct EventHandler : IEventHandler {
            std::function<void(const Event&)> handler;

            EventHandler(std::function<void(const Event&)> h) : handler(std::move(h)) {}

            void handle(const void* event) override {
                handler(*static_cast<const Event*>(event));
            }
        };

        struct QueuedEvent {
            std::unique_ptr<void, void(*)(void*)> data;
            std::function<void(const void*)> trigger_func;

            template<typename Event>
            QueuedEvent(Event&& event)
                : data(new Event(std::forward<Event>(event)), [](void* ptr) { delete static_cast<Event*>(ptr); })
                , trigger_func([this](const void*) {
                    auto* evt = static_cast<const Event*>(data.get());
                }) {}
        };


        struct IEventIdentifierHandler {
            virtual ~IEventIdentifierHandler() = default;
            virtual void handle() = 0;
        };

        template<typename Event>
       struct EventIdentifierHandler : IEventIdentifierHandler {
            std::function<void()> handler;

            EventIdentifierHandler(std::function<void()> h) : handler(std::move(h)) {}

            void handle() override {
                handler();
            }
        };

        std::conditional_t<Config::EventAsData,
         std::unordered_map<entt::id_type, std::unordered_map<SubscribeId, std::unique_ptr<IEventHandler>>>,
         std::unordered_map<entt::id_type, std::unordered_map<SubscribeId, std::unique_ptr<IEventIdentifierHandler>>>> m_handlers;

        std::conditional_t<Config::EnableQueue,
            std::unordered_map<entt::id_type, std::vector<std::function<void()>>>,
            std::monostate> m_eventQueue;

        SubscribeId m_nextSubscribeId = 1;

    public:
        template<typename Event>
       void trigger(const Event& event)
           requires (Config::EnableTrigger && Config::EventAsData)
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto it = m_handlers.find(eventTypeId);
            if (it != m_handlers.end()) {
                for (const auto& [id, handler] : it->second) {
                    handler->handle(&event);
                }
            }
        }

        template<typename Event>
       void trigger()
           requires (Config::EnableTrigger && !Config::EventAsData)
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto it = m_handlers.find(eventTypeId);
            if (it != m_handlers.end()) {
                for (const auto& [id, handler] : it->second) {
                    handler->handle();
                }
            }
        }

        template<typename Event>
       void enqueue(Event&& event)
           requires (Config::EnableQueue && Config::EventAsData)
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto triggerLambda = [this, evt = std::forward<Event>(event)]() mutable {
                this->trigger(evt);
            };

            m_eventQueue[eventTypeId].emplace_back(std::move(triggerLambda));
        }

        template<typename Event>
        void enqueue()
            requires (Config::EnableQueue && !Config::EventAsData)
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto triggerLambda = [this]() {
                this->template trigger<Event>();
            };

            m_eventQueue[eventTypeId].emplace_back(std::move(triggerLambda));
        }


        template<typename Event>
        void update()
            requires Config::EnableQueue
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto it = m_eventQueue.find(eventTypeId);
            if (it != m_eventQueue.end()) {
                auto& queue = it->second;
                for (auto& triggerFunc : queue) {
                    triggerFunc();
                }
                queue.clear();
            }
        }

        void updateAll()
            requires Config::EnableQueue
        {
            for (auto& [typeId, queue] : m_eventQueue) {
                for (auto& triggerFunc : queue) {
                    triggerFunc();
                }
                queue.clear();
            }
        }

        template<typename Event, typename Func>
        SubscribeId subscribe(Func&& func)
            requires Config::EventAsData
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto subscribeId = m_nextSubscribeId++;

            auto handler = std::make_unique<EventHandler<Event>>(
                std::function<void(const Event&)>(std::forward<Func>(func))
            );

            m_handlers[eventTypeId][subscribeId] = std::move(handler);

            return subscribeId;
        }
        template<typename Event, typename Func>
        SubscribeId subscribe(Func&& func)
            requires (!Config::EventAsData)
        {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto subscribeId = m_nextSubscribeId++;

            auto handler = std::make_unique<EventIdentifierHandler<Event>>(
                std::function<void()>(std::forward<Func>(func))
            );

            m_handlers[eventTypeId][subscribeId] = std::move(handler);

            return subscribeId;
        }


        template<typename Event>
        void unsubscribe(SubscribeId subscribeId) {
            constexpr auto eventTypeId = getEventTypeId<Event>();

            auto it = m_handlers.find(eventTypeId);
            if (it != m_handlers.end()) {
                it->second.erase(subscribeId);
                if (it->second.empty()) {
                    m_handlers.erase(it);
                }
            }
        }

        template<typename Event>
        void unsubscribeAll() {
            constexpr auto eventTypeId = getEventTypeId<Event>();
            m_handlers.erase(eventTypeId);
        }

        void unsubscribe(SubscribeId subscribeId) {
            for (auto& [typeId, handlers] : m_handlers) {
                auto it = handlers.find(subscribeId);
                if (it != handlers.end()) {
                    handlers.erase(it);
                    if (handlers.empty()) {
                        m_handlers.erase(typeId);
                    }
                    return;
                }
            }
        }
    };
    template<typename Config = EventSystemConfig::Full>
    using EventDispatcher = IEventSystem<Config>;
}
#endif //EVENTSYSTEM_H