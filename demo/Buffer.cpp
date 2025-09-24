#include "Buffer.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

Buffer::~Buffer()
{
    destroy();
}

bool Buffer::create(const wgpu::Device& device, wgpu::BufferUsage usage, size_t size)
{
    destroy();

    wgpu::BufferDescriptor desc{
        .usage = usage,
        .size = size,
        .mappedAtCreation = false
    };

    mHandle = device.CreateBuffer(&desc);
    if (!mHandle) {
        std::cerr << "Failed to create buffer!" << std::endl;
        assert(0);
        return false;
    }

    return true;
}

bool Buffer::create(const wgpu::Device& device, wgpu::BufferUsage usage, uint64_t size, const void* data)
{
    destroy();

    if (!create(device, usage, size)) {
        return false;
    }

    // Copy from RAM to VRAM
    device.GetQueue().WriteBuffer(mHandle, 0, data, size);

    return true;
}

void Buffer::destroy()
{
    mHandle = nullptr;
}

void Buffer::write(const wgpu::Queue& queue, const void* data, size_t size, uint64_t offset)
{
    queue.WriteBuffer(mHandle, offset, data, size);
}

DAWN_END_NAMESPACE
