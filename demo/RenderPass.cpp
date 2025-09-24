#include "RenderPass.h"

#include <iostream>

#include <webgpu/webgpu.h>

DAWN_BEGIN_NAMESPACE

RenderPass::~RenderPass()
{
	destroy();
}

bool RenderPass::begin(const wgpu::TextureView& textureView, wgpu::CommandEncoder& commandEncoder/*, const wgpu::TextureView& depthView*/)
{
	destroy();

	// Color attachment
	wgpu::RenderPassColorAttachment colorAttachment{};
	colorAttachment.view = textureView;
	colorAttachment.resolveTarget = nullptr;
	colorAttachment.loadOp = wgpu::LoadOp::Clear;
	colorAttachment.storeOp = wgpu::StoreOp::Store;
	colorAttachment.clearValue = { 0.1, 0.1, 0.1, 1.0 };
	/*
	// Depth-stencil attachment
	wgpu::RenderPassDepthStencilAttachment depthAttachment{};
	depthAttachment.view = depthView;

	// Depth
	depthAttachment.depthClearValue = 1.0f;
	depthAttachment.depthLoadOp = wgpu::LoadOp::Clear;
	depthAttachment.depthStoreOp = wgpu::StoreOp::Store;

	// Leave stencil undefined (since your depth format has no stencil)
	depthAttachment.stencilLoadOp = wgpu::LoadOp::Undefined;
	depthAttachment.stencilStoreOp = wgpu::StoreOp::Undefined;
	*/
	// Render pass descriptor
	wgpu::RenderPassDescriptor renderPassDescriptor{};
	renderPassDescriptor.colorAttachmentCount = 1;
	renderPassDescriptor.colorAttachments = &colorAttachment;
	//renderPassDescriptor.depthStencilAttachment = &depthAttachment;
	renderPassDescriptor.timestampWrites = nullptr;

	mHandle = commandEncoder.BeginRenderPass(&renderPassDescriptor);
	if (!mHandle) {
		std::cerr << "Could not begin render pass!" << std::endl;
		assert(0);
		destroy();
		return false;
	}

	return true;
}

void RenderPass::end()
{
	mHandle.End();
}

void RenderPass::destroy()
{
	mHandle = nullptr;
}

void RenderPass::setPipeline(wgpu::RenderPipeline pipeline) const
{
	mHandle.SetPipeline(pipeline);
}

void RenderPass::setVertexBuffer(wgpu::Buffer buffer, uint32_t slot) const
{
	mHandle.SetVertexBuffer(slot, buffer, 0, WGPU_WHOLE_SIZE);
}

void RenderPass::setIndexBuffer(wgpu::Buffer buffer, uint32_t slot) const
{
	mHandle.SetIndexBuffer(buffer, wgpu::IndexFormat::Uint32, 0, WGPU_WHOLE_SIZE);
}

void RenderPass::setBindGroup(uint32_t index, wgpu::BindGroup bindGroup, uint32_t dynamicOffsetCount, const uint32_t* dynamicOffsets) const
{
	mHandle.SetBindGroup(index, bindGroup, dynamicOffsetCount, dynamicOffsets);
}

void RenderPass::drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t baseVertex, uint32_t baseInstance) const
{
	mHandle.DrawIndexed(indexCount, instanceCount, firstIndex, baseVertex, baseInstance);
}

DAWN_END_NAMESPACE
