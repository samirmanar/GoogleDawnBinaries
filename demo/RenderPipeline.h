#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class RenderPipeline
{
public:
	~RenderPipeline();

    bool create(const wgpu::Device& device, const wgpu::ShaderModule& module,
        const wgpu::BindGroupLayout& bindGroupLayout, wgpu::TextureFormat format);
    void destroy();

    operator wgpu::RenderPipeline() {
		return mHandle;
	}

protected:
    wgpu::RenderPipeline mHandle = nullptr;
    wgpu::PipelineLayout mLayout = nullptr;
};

DAWN_END_NAMESPACE
