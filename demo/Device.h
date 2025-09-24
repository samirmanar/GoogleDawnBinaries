#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class Device
{
public:
    ~Device();

    bool create(wgpu::Adapter adapter);
    void destroy();

    wgpu::Queue getQueue() const {
        return mQueue;
    }

    operator wgpu::Device() {
        return mHandle;
    }

protected:
    wgpu::Device mHandle = nullptr;
    wgpu::Queue mQueue = nullptr;
};

DAWN_END_NAMESPACE
