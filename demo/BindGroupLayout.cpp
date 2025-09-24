#include "BindGroupLayout.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

BindGroupLayout::~BindGroupLayout()
{
    destroy();
}

void BindGroupLayout::setDefault(wgpu::BindGroupLayoutEntry& bindingLayout)
{
	bindingLayout.buffer.nextInChain = nullptr;
	bindingLayout.buffer.type = wgpu::BufferBindingType::BindingNotUsed;
	bindingLayout.buffer.hasDynamicOffset = false;

	bindingLayout.sampler.nextInChain = nullptr;
	bindingLayout.sampler.type = wgpu::SamplerBindingType::BindingNotUsed;

	bindingLayout.storageTexture.nextInChain = nullptr;
	bindingLayout.storageTexture.access = wgpu::StorageTextureAccess::BindingNotUsed;
	bindingLayout.storageTexture.format = wgpu::TextureFormat::Undefined;
	bindingLayout.storageTexture.viewDimension = wgpu::TextureViewDimension::Undefined;

	bindingLayout.texture.nextInChain = nullptr;
	bindingLayout.texture.multisampled = false;
	bindingLayout.texture.sampleType = wgpu::TextureSampleType::BindingNotUsed;
	bindingLayout.texture.viewDimension = wgpu::TextureViewDimension::Undefined;
}

bool BindGroupLayout::create(const wgpu::Device& device, uint64_t minBindingSize, uint32_t bindingIndex)
{
    destroy();

    // Define binding layout
	wgpu::BindGroupLayoutEntry bindingLayout{};
	setDefault(bindingLayout);

    // The binding index as used in the @binding attribute in the shader
	bindingLayout.binding = bindingIndex;

	// The stage that needs to access this resource
	bindingLayout.visibility = wgpu::ShaderStage::Vertex | wgpu::ShaderStage::Fragment;
	bindingLayout.buffer.type = wgpu::BufferBindingType::Uniform;
	bindingLayout.buffer.minBindingSize = minBindingSize;

    wgpu::BindGroupLayoutDescriptor bindingLayoutDesc{};
    bindingLayoutDesc.entryCount = 1;
    bindingLayoutDesc.entries = &bindingLayout;

    mHandle = device.CreateBindGroupLayout(&bindingLayoutDesc);
    if (mHandle == nullptr) {
        std::cerr << "Bing Group Layout creation failed!\n";
        return false;
    }

    return true;
}

void BindGroupLayout::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
