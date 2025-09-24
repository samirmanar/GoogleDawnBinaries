#pragma once

#include <stdint.h>

#include <webgpu/webgpu_cpp.h>

#include "Namespace.h"

DAWN_BEGIN_NAMESPACE

class RenderPass
{
public:
	RenderPass() = default;

	explicit RenderPass(WGPURenderPassEncoder handle)
		: mHandle(handle) {
	}

	explicit RenderPass(wgpu::RenderPassEncoder handle)
		: mHandle(handle) {
	}

	RenderPass(RenderPass&& other) noexcept
		: mHandle(std::move(other.mHandle)) {
		other.mHandle = nullptr;
	}

	RenderPass& operator=(RenderPass&& other) noexcept {
		if (this != &other) {
			destroy();
			mHandle = std::move(other.mHandle);
			other.mHandle = nullptr;
		}
		return *this;
	}

	RenderPass(const RenderPass&) = delete;
	RenderPass& operator=(const RenderPass&) = delete;

	~RenderPass();

	bool begin(const wgpu::TextureView& textureView, wgpu::CommandEncoder& commandEncoder/*, const wgpu::TextureView& depthView*/);
	void end();

	void destroy();
	
	void setPipeline(wgpu::RenderPipeline pipeline) const;

	void setVertexBuffer(wgpu::Buffer buffer, uint32_t slot) const;
	void setIndexBuffer(wgpu::Buffer buffer, uint32_t slot) const;

	void setBindGroup(uint32_t index, wgpu::BindGroup bindGroup, 
		uint32_t dynamicOffsetCount = 0, const uint32_t* dynamicOffsets = nullptr) const;

	void drawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, 
		uint32_t firstIndex = 0, uint32_t baseVertex = 0, uint32_t baseInstance = 0) const;

	operator wgpu::RenderPassEncoder() {
		return mHandle;
	}

private:
	wgpu::RenderPassEncoder mHandle = nullptr;
};

DAWN_END_NAMESPACE
