//
// Created by Administrator on 2025/8/15.
//

#ifndef FLOWCONTROL_H
#define FLOWCONTROL_H
#include "../Base/TokenGraph.h"
namespace FCT {
    using SubmitTicker = std::function<void()>;
    using SyncTicker = std::function<void()>;
    class FlowControl
    {
    public:
        auto& submitTickers() { return m_submitTickers; }
        auto& syncTickers()  { return m_syncTickers; }
        void executeSubmitTickers();
        void executeSyncTickers();
    private:
        TokenGraph<std::string, SubmitTicker> m_submitTickers;
        TokenGraph<std::string, SyncTicker> m_syncTickers;
    };
}
#endif //FLOWCONTROL_H
