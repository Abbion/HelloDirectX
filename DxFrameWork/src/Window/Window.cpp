#include "Window.h"
#include <iostream>

#pragma comment(lib, "d3d11.lib")

using namespace FW;
using namespace DirectX;

Window::Window(unsigned width, unsigned height, const std::string& name) :
	m_windowDimensions{ width, height },
	m_windowName{ name }
{
	//Setup GLFW Window
	if (m_globalInit == false)
	{
		glfwSetErrorCallback(error_callback);

		if (!glfwInit())
			exit(EXIT_FAILURE);

		m_globalInit = true;
	}

	m_systemWindow = glfwCreateWindow(m_windowDimensions.x, m_windowDimensions.y, m_windowName.c_str(), NULL, NULL);

	if (!m_systemWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_systemWindow);
	glfwSwapInterval(1);

	//Setup DirectX
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = glfwGetWin32Window(m_systemWindow);
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;


	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_context
	);

	ID3D11Resource* backBufferTex{ nullptr };
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBufferTex));
	m_device->CreateRenderTargetView(backBufferTex, nullptr, &m_backBufferView);
	backBufferTex->Release();
}

const bool Window::IsOpen() const
{
	return glfwWindowShouldClose(m_systemWindow) == false;
}

void Window::PoolEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	const float color[] = { 0.0f, 1.0f, 0.5f, 1.0f };
	m_context->ClearRenderTargetView(m_backBufferView, color);
	m_swapChain->Present(1u, 0u);
}

void Window::Terminate()
{
	glfwTerminate();
}

void Window::error_callback(int error, const char* description)
{
	std::cout << "GLFW error id:" << error << " - " << description << std::endl;
}
