#pragma once
#include "Swapchain.hpp"
#include "RGLD3D12.hpp"
#include <d3d12.h>
#include <dxgi1_5.h>

namespace RGL {
	struct DeviceD3D12;
	struct SurfaceD3D12;
	struct TextureD3D12;
	
	struct SwapchainD3D12 : public ISwapchain {
		constexpr static uint8_t g_NumFrames = 3;

		ComPtr<IDXGISwapChain4> swapchain;
		const std::shared_ptr<DeviceD3D12> owningDevice;
		ComPtr<ID3D12DescriptorHeap> m_RTVDescriptorHeap;
		ComPtr<ID3D12Resource> backbuffers[g_NumFrames];
		std::vector<TextureD3D12> backbufferTextures;

		SwapchainD3D12(decltype(owningDevice), std::shared_ptr<SurfaceD3D12>, int width, int height);
		void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device,
			ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);

		// ISwapchain
		void Resize(uint32_t width, uint32_t height) final;
		void GetNextImage(uint32_t* index, std::shared_ptr<ISemaphore> semaphore) final;
		ITexture* ImageAtIndex(uint32_t index) final;
		void Present(const SwapchainPresentConfig&) final;
		virtual ~SwapchainD3D12();
	};
}