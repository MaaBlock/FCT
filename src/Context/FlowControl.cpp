#include "./FlowControl.h"
namespace FCT
{
    void FlowControl::executeSubmitTickers()
    {
        auto order = m_submitTickers.order();
        for (auto& ticker : order) {
            ticker();
        }
    }

    void FlowControl::executeSyncTickers()
    {
        auto order = m_syncTickers.order();
        for (auto& ticker : order) {
            ticker();
        }
    }
}
