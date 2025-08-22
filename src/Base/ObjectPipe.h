//
// Created by Administrator on 2025/8/21.
//

#ifndef OBJECTPIPE_H
#define OBJECTPIPE_H
#include "../ThirdParty.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
namespace FCT {
    using SubscribeId = std::size_t;
    struct IObjectDispatcher {
        virtual ~IObjectDispatcher() = default;
        virtual void unsubscribe(SubscribeId id) = 0;
    };
    template<typename Token,typename Object>
    struct ObjectDispatcher : public IObjectDispatcher {
        size_t index = 0;
        boost::unordered_flat_map<SubscribeId, std::function<void(Object&)>> get;
        boost::unordered_flat_map<SubscribeId, std::function<void()>> lost;
        Object* object = nullptr;
        std::unique_ptr<Object> ownedObject = nullptr;
        Token token;
        ObjectDispatcher(const Token& t) : token(t) {}
        SubscribeId subscribeGet(std::function<void(Object&)> getFunc) {
            std::size_t seed = 0;
            boost::hash_combine(seed, index++);
            boost::hash_combine(seed, entt::type_hash<Object>::value());
            boost::hash_combine(seed, std::hash<Token>{}(token));
            get[seed] = getFunc;

            if (object) {
                getFunc(*object);
            }

            return seed;
        }
        SubscribeId subscribeLost(std::function<void()> lostFunc) {
            std::size_t seed = 0;
            boost::hash_combine(seed, index++);
            boost::hash_combine(seed, entt::type_hash<Object>::value());
            boost::hash_combine(seed, std::hash<Token>{}(token));
            lost[seed] = lostFunc;
            return seed;
        }

        void unsubscribe(SubscribeId id) override
        {
            if (get.contains(id)) {
                get.erase(id);
            }
            if (lost.contains(id)) {
                lost.erase(id);
            }
        }

        void push(Object* obj) {
            ownedObject.reset();
            object = obj;
            for (const auto& [id, callback] : get) {
                callback(*obj);
            }
        }
        void pushOwned(Object&& obj) {
            ownedObject = std::make_unique<Object>(std::move(obj));
            object = ownedObject.get();
            for (const auto& [id, callback] : get) {
                callback(*object);
            }
        }

        void pop() {
            for (const auto& [id, callback] : lost) {
                callback();
            }
            object = nullptr;
            ownedObject.reset();
        }
        void trigger(Object* obj) {
            for (const auto& [id, callback] : get) {
                callback(*obj);
            }
            for (const auto& [id, callback] : lost) {
                callback();
            }
        }
    };
    template<typename Token>
    class PipePort;
    template<typename Token>
    class ObjectPipe {
    private:
        std::unordered_map<Token, std::unordered_map<std::size_t, std::unique_ptr<IObjectDispatcher>>> m_tokenDispatchers;
        template<typename Object>
        ObjectDispatcher<Token, Object>* getOrCreateDispatcher(const Token& token) {
            auto typeHash = entt::type_hash<Object>::value();

            if (m_tokenDispatchers[token].find(typeHash) == m_tokenDispatchers[token].end()) {
                m_tokenDispatchers[token][typeHash] = std::make_unique<ObjectDispatcher<Token, Object>>(token);
            }

            return static_cast<ObjectDispatcher<Token, Object>*>(m_tokenDispatchers[token][typeHash].get());
        }
    public:
        template<typename Object, typename FuncGet>
        SubscribeId subscribe(const Token& token, FuncGet&& getFunc) {
            auto dispatcher = getOrCreateDispatcher<Object>(token);
            return dispatcher->subscribeGet([getFunc](Object& obj) {
                getFunc(obj);
            });
        }
        template<typename Object, typename FuncGet, typename FuncLost>
        std::pair<SubscribeId, SubscribeId> subscribe(const Token& token,
                                                     FuncGet&& getFunc,
                                                     FuncLost&& lostFunc) {
            auto dispatcher = getOrCreateDispatcher<Object>(token);
            auto getId = dispatcher->subscribeGet([getFunc = std::forward<FuncGet>(getFunc)](Object& obj) {
                getFunc(obj);
            });
            auto lostId = dispatcher->subscribeLost([lostFunc = std::forward<FuncLost>(lostFunc)]() {
                lostFunc();
            });
            return {getId, lostId};
        }
        template<typename Object>
        void provide(const Token& token, Object& object) {
            auto dispatcher = getOrCreateDispatcher<std::decay_t<Object>>(token);
            dispatcher->push(&object);
        }

        template<typename Object>
        void provide(const Token& token, Object&& object) {
            auto dispatcher = getOrCreateDispatcher<std::decay_t<Object>>(token);
            dispatcher->pushOwned(std::forward<Object>(object));
        }
        template<typename Object>
        void remove(const Token& token) {
            auto dispatcher = getOrCreateDispatcher<Object>(token);
            dispatcher->pop();
        }
        template<typename Object>
       void trigger(const Token& token, Object* object) {
            auto dispatcher = getOrCreateDispatcher<Object>(token);
            dispatcher->trigger(object);
        }
        void unsubscribe(const Token& token, SubscribeId id) {
            if (auto tokenIt = m_tokenDispatchers.find(token); tokenIt != m_tokenDispatchers.end()) {
                for (auto& [typeHash, dispatcher] : tokenIt->second) {
                    dispatcher->unsubscribe(id);
                }
            }
        }
        PipePort<Token> getPort(const Token& token);
    };
} // FCT

#endif //OBJECTPIPE_H
