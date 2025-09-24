#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class CommandEncoder
{
public:
	~CommandEncoder();

    bool create(const wgpu::Device& device);
    void destroy();

    wgpu::RenderPassEncoder beginRenderPass(wgpu::RenderPassDescriptor const* descriptor);
    wgpu::CommandBuffer finish();

    operator wgpu::CommandEncoder&() {
        return mHandle;
    }

protected:
   wgpu::CommandEncoder mHandle = nullptr;

};

DAWN_END_NAMESPACE
