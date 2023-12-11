#pragma once
#include "Core.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>

#include "Graphics/Graphics.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"
#include "Events/EventQueue.h"

#include <DirectXMath.h>

#include <string>
#include <memory>
#include <wrl.h>

namespace FW
{
	class DXFW_API Window
	{
	public:
		Window(unsigned width, unsigned height, const std::string& name);

		const DirectX::XMUINT2 GetDimensions() const { return m_windowDimensions; }
		const bool IsOpen() const;

		Graphics& GetGraphics() { return *m_graphics; }
		Keyboard& GetKeyboard() { return m_keyboard; }
		Mouse& GetMouse()		{ return m_mouse; }

		std::shared_ptr<EventQueue>& GetEventQueue() { return m_eventQueue; }

		void HandleInternalEvents();
		void PoolEvents();
		void Close();

		static void Terminate();

	private:
		void InitCallBacks();
		HWND GetNativeWindowHandle() const { return glfwGetWin32Window(m_systemWindow); }

	private:
		struct WindowPointerDataStruct {
			std::shared_ptr<EventQueue> eventQueue;
		};

		WindowPointerDataStruct m_windowPointerDataStruct;

		DirectX::XMUINT2 m_windowDimensions{ 1, 1 };
		std::string m_windowName;

		GLFWwindow* m_systemWindow;

		std::shared_ptr<EventQueue> m_eventQueue;
		std::unique_ptr<Graphics> m_graphics;
		Keyboard m_keyboard;
		Mouse m_mouse;

		inline static bool m_globalInit{ false };

		friend Graphics;
	};
}