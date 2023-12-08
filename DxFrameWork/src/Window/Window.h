#pragma once
#include "Core.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>

#include <DirectXMath.h>
#include <d3d11.h>

#include <string>

namespace FW
{
	class DXFW_API Window
	{
	public:
		Window(unsigned width, unsigned height, const std::string& name);

		const DirectX::XMUINT2 GetDimensions() const { return m_windowDimensions; }
		const bool IsOpen() const;

		void PoolEvents();
		void SwapBuffers();
		static void Terminate();

	private:
		void static error_callback(int error, const char* description);

	private:
		DirectX::XMUINT2 m_windowDimensions{ 1, 1 };
		std::string m_windowName;

		GLFWwindow* m_systemWindow;

		ID3D11Device* m_device{ nullptr };
		IDXGISwapChain* m_swapChain{ nullptr };
		ID3D11DeviceContext* m_context{ nullptr };
		ID3D11RenderTargetView* m_backBufferView{ nullptr };

		inline static bool m_globalInit{ false };
	};
}