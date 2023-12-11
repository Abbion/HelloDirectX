#pragma once
#include "Core.h"

#include <DirectXMath.h>
#include <d3d11.h>

#include <wrl.h>

namespace FW
{
	class Window;

	class DXFW_API Graphics
	{
	public:
		Graphics(const Window& window);

		Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice()				{ return m_device; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> & GetContext()		{ return m_context; }
		Microsoft::WRL::ComPtr<IDXGISwapChain>& GetSwapChain()			{ return m_swapChain; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& GetBackBuffer() { return m_backBufferView; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_device{ nullptr };
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{ nullptr };
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{ nullptr };
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_backBufferView{ nullptr };
	};
}