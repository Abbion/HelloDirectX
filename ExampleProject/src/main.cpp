#include "DxFrameWork.h"
#include <iostream>

int main()
{
	FW::Window window(800, 600, "Example");
	
	auto& graphics = window.GetGraphics();
	auto& swapChain = graphics.GetSwapChain();
	auto& context = graphics.GetContext();
	auto& device = graphics.GetDevice();
	auto& backBufferView = graphics.GetBackBuffer();

	auto& keyboard = window.GetKeyboard();
	auto& mouse = window.GetMouse();

	//Init=============================================================
	//Load data, create meshes and objects

	//=================================================================

	while (window.IsOpen())
	{
		window.HandleInternalEvents();

		//Handle event==============================================
		auto eventQueue = window.GetEventQueue();
		while (eventQueue->HasPenddingEvents())
		{
			const auto currentEvent = eventQueue->PopEvent();

			if (currentEvent->GetType() == FW::EventType::KeyUp) {
				const auto key = static_cast<FW::KeyDownEvent*>(currentEvent.get())->GetVal();

				if (key == FW::Keyboard::Key::ESCAPE)
					window.Close();
			}
		}
		//==========================================================

		//Update====================================================
		
		//==========================================================

		//Render====================================================
		const float color_f[] = { 0.5f, 0.2f, 0.2f, 1.0f };
		context->ClearRenderTargetView(backBufferView.Get(), color_f);

		swapChain->Present(1, 0);
		window.PoolEvents();
	}

	FW::Window::Terminate();

	return 0;
}