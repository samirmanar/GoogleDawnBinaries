#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class BindGroup
{
public:
	~BindGroup();

    bool create(const wgpu::Device& device, const wgpu::BindGroupLayout& bindGroupLayout, const wgpu::Buffer& uniformBuffer, size_t uniformBufferSize);
    void destroy();

    operator wgpu::BindGroup() {
		return mHandle;
	}

protected:
    wgpu::BindGroup mHandle = nullptr;
};

DAWN_END_NAMESPACE
