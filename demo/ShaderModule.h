#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class ShaderModule
{
public:
	~ShaderModule();

    bool loadFromFile(const wgpu::Device& device, const char* filename);
    void destroy();

    operator wgpu::ShaderModule() {
        return mHandle;
    }

protected:
    wgpu::ShaderModule mHandle = nullptr;
};

DAWN_END_NAMESPACE
