#if RGL_VK_AVAILABLE
#include "VkSynchronization.hpp"
#include "VkDevice.hpp"
#include "RGLVk.hpp"

namespace RGL {
	FenceVk::FenceVk(decltype(owningDevice) device, bool preSignaled) : owningDevice(device)
	{
		VkFenceCreateInfo fenceInfo{
		  .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		  .flags = preSignaled? VK_FENCE_CREATE_SIGNALED_BIT : VkFenceCreateFlags(0)
		};
		VK_CHECK(vkCreateFence(owningDevice->device, &fenceInfo, nullptr, &fence));
	}
	void FenceVk::Wait()
	{
		vkWaitForFences(owningDevice->device, 1, &fence, VK_TRUE, UINT64_MAX);
	}
	void FenceVk::Reset()
	{
		vkResetFences(owningDevice->device, 1, &fence);
	}
	FenceVk::~FenceVk()
	{
		vkDestroyFence(owningDevice->device, fence, nullptr);
	}
	SemaphoreVk::SemaphoreVk(decltype(owningDevice) device) : owningDevice(device)
	{
		VkSemaphoreCreateInfo semaphoreInfo{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
		};
		VK_CHECK(vkCreateSemaphore(owningDevice->device, &semaphoreInfo, nullptr, &semaphore));
	}
	SemaphoreVk::~SemaphoreVk()
	{
		vkDestroySemaphore(owningDevice->device, semaphore, nullptr);
	}
}
#endif