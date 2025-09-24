#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class Buffer
{
public:
    ~Buffer();

    bool create(const wgpu::Device& device, wgpu::BufferUsage usage, size_t size);
    bool create(const wgpu::Device& device, wgpu::BufferUsage usage, uint64_t size, const void* data);
    void destroy();

    void write(const wgpu::Queue& queue, const void* data, size_t size, uint64_t offset = 0);

    operator wgpu::Buffer() {
        return mHandle;
    }

protected:
    wgpu::Buffer mHandle = nullptr;

};

DAWN_END_NAMESPACE
