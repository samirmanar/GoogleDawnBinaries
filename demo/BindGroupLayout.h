
#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class BindGroupLayout
{
public:
	~BindGroupLayout();

    bool create(const wgpu::Device& device, uint64_t minBindingSize, uint32_t bindingIndex = 0);
    void destroy();

    operator wgpu::BindGroupLayout() {
		return mHandle;
	}

protected:
    void setDefault(wgpu::BindGroupLayoutEntry& bindingLayout);

    wgpu::BindGroupLayout mHandle = nullptr;
};

DAWN_END_NAMESPACE
