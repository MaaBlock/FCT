#ifndef FCT_CONTEXT_IH
#define FCT_CONTEXT_IH
#include "../UI/Window.h"
namespace FCT {


	inline void Context::submitThread()
	{
		while (m_ctxRunning) {

			_waitForNextFrame();
			auto order = m_submitTickers.order();
			for (auto& ticker : order) {
				ticker();
			}
			_currentFlush();
		}
	}
	inline void Context::flush()
	{
		m_logicTask.consume_all([](LogicTaskData*& data) {
			data->task();
			FCT_DELETE(data);
		});
		_waitCurrentFlush();
		auto tickers = m_syncTickers.order();
		for (auto ticker : tickers)
		{
			ticker();
		}
		_nextFrame();
	}

	inline void Context::maxFrameInFlight(uint32_t maxFrameInFlight)
	{
		m_maxFrameInFlight = maxFrameInFlight;
		m_cmdGraph->maxFrameInFlight(m_maxFrameInFlight);
	}

	inline RHI::DescriptorPool* Context::getDescriptorPool()
	{
		return m_descriptorPool;
	}

	template <typename T>
	inline T* Context::createResource()
	{
		return m_resourceDevice->createResource<T>();
	}
}
#endif