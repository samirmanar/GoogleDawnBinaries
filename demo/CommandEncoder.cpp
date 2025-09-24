#include "CommandEncoder.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

CommandEncoder::~CommandEncoder()
{
    destroy();
}

bool CommandEncoder::create(const wgpu::Device& device)
{
    destroy();

    wgpu::CommandEncoderDescriptor descriptor {};
    mHandle = device.CreateCommandEncoder(&descriptor);
    if (!mHandle) {
        std::cerr << "Failed to create command encoder!\n";
        return false;
    }

    return true;
}

void CommandEncoder::destroy()
{
    mHandle = nullptr;
}

wgpu::RenderPassEncoder CommandEncoder::beginRenderPass(wgpu::RenderPassDescriptor const* descriptor)
{
    return mHandle.BeginRenderPass(descriptor);
}

wgpu::CommandBuffer CommandEncoder::finish()
{
    return mHandle.Finish();
}

DAWN_END_NAMESPACE
