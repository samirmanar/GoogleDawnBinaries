#include "BindGroup.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

BindGroup::~BindGroup()
{
    destroy();
}

bool BindGroup::create(const wgpu::Device& device, const wgpu::BindGroupLayout& bindGroupLayout, const wgpu::Buffer& uniformBuffer, size_t uniformBufferSize)
{
    destroy();

    // Create a binding
    wgpu::BindGroupEntry binding{};
	binding.nextInChain = nullptr;

    // The index of the binding (the entries in bindGroupDesc can be in any order)
	binding.binding = 0;
	// The buffer it is actually bound to
	binding.buffer = uniformBuffer;

    // We can specify an offset within the buffer, so that a single buffer can hold
	// multiple uniform blocks.
	binding.offset = 0;
	// And we specify again the size of the buffer.
	binding.size = uniformBufferSize;

    // A bind group contains one or multiple bindings
	wgpu::BindGroupDescriptor bindGroupDesc{};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = bindGroupLayout;
    
	// There must be as many bindings as declared in the layout!
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &binding;

    mHandle = device.CreateBindGroup(&bindGroupDesc);
    if (mHandle == nullptr) {
        std::cerr << "Bing Group creation failed!\n";
        return false;
    }

    return true;
}

void BindGroup::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
