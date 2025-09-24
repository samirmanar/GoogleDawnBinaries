#include "RenderPipeline.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

RenderPipeline::~RenderPipeline()
{
}

bool RenderPipeline::create(const wgpu::Device& device, const wgpu::ShaderModule& module, 
	const wgpu::BindGroupLayout& bindGroupLayout, wgpu::TextureFormat format)
{
    destroy();

    std::vector<wgpu::VertexBufferLayout> vertexBufferLayouts(3);	// We have 3 vertex buffers

	// Describe the position attribute
	wgpu::VertexAttribute positionAttrib;
    positionAttrib.shaderLocation = 0; // @location(0)
	positionAttrib.format = wgpu::VertexFormat::Float32x3;	// 3 floats for x, y, z
	positionAttrib.offset = 0;

    vertexBufferLayouts[0].attributeCount = 1;
	vertexBufferLayouts[0].attributes = &positionAttrib;
    vertexBufferLayouts[0].arrayStride = 3 * sizeof(float); // 3 floats for x, y, z
	vertexBufferLayouts[0].stepMode = wgpu::VertexStepMode::Vertex;

	// Describe the color attribute
	wgpu::VertexAttribute colorAttrib;
    colorAttrib.shaderLocation = 1; // @location(1)
	colorAttrib.format = wgpu::VertexFormat::Float32x3; // 3 floats for r, g, b
	colorAttrib.offset = 0;

	vertexBufferLayouts[1].attributeCount = 1;
	vertexBufferLayouts[1].attributes = &colorAttrib;
	vertexBufferLayouts[1].arrayStride = 3 * sizeof(float); // 3 floats for r, g, b
	vertexBufferLayouts[1].stepMode = wgpu::VertexStepMode::Vertex;

	// Describe the normal attribute
	wgpu::VertexAttribute normalAttrib;
    normalAttrib.shaderLocation = 2; // @location(1)
	normalAttrib.format = wgpu::VertexFormat::Float32x3; // 3 floats for x, y, z
	normalAttrib.offset = 0;

	vertexBufferLayouts[2].attributeCount = 1;
	vertexBufferLayouts[2].attributes = &normalAttrib;
	vertexBufferLayouts[2].arrayStride = 3 * sizeof(float); // 3 floats for x, y, z
	vertexBufferLayouts[2].stepMode = wgpu::VertexStepMode::Vertex;

    wgpu::BlendState blendState{};
	blendState.color.srcFactor = wgpu::BlendFactor::SrcAlpha;
	blendState.color.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
	blendState.color.operation = wgpu::BlendOperation::Add;
	blendState.alpha.srcFactor = wgpu::BlendFactor::Zero;
	blendState.alpha.dstFactor = wgpu::BlendFactor::One;
	blendState.alpha.operation = wgpu::BlendOperation::Add;

    wgpu::ColorTargetState colorTarget{};
	colorTarget.format = format;
	colorTarget.blend = &blendState;
	colorTarget.writeMask = wgpu::ColorWriteMask::All; // We could write to only some of the color channels.

    // We tell that the programmable fragment shader stage is described
	// by the function called 'fs_main' in the shader module.
	wgpu::FragmentState fragmentState{};
	fragmentState.module = module;
	fragmentState.entryPoint = "fs_main";
	fragmentState.constantCount = 0;
	fragmentState.constants = nullptr;
    fragmentState.targetCount = 1;
	fragmentState.targets = &colorTarget;

    wgpu::RenderPipelineDescriptor pipelineDesc{};
    pipelineDesc.vertex.bufferCount = static_cast<uint32_t>(vertexBufferLayouts.size());
	pipelineDesc.vertex.buffers = vertexBufferLayouts.data();
    pipelineDesc.vertex.module = module;
	pipelineDesc.vertex.entryPoint = "vs_main";
	pipelineDesc.vertex.constantCount = 0;
	pipelineDesc.vertex.constants = nullptr;

    pipelineDesc.fragment = &fragmentState;

    // Each sequence of 3 vertices is considered as a triangle
    pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;

    // When not specified, vertices are considered sequentially.
	pipelineDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;

    // The face orientation is defined by assuming that when looking
	// from the front of the face, its corner vertices are enumerated
	// in the counter-clockwise (CCW) order.
	pipelineDesc.primitive.frontFace = wgpu::FrontFace::CCW;

    // But the face orientation does not matter much because we do not
	// cull (i.e. "hide") the faces pointing away from us (which is often
	// used for optimization).
	pipelineDesc.primitive.cullMode = wgpu::CullMode::None;

    // We do not use stencil/depth testing for now
	pipelineDesc.depthStencil = nullptr;

    // Samples per pixel
	pipelineDesc.multisample.count = 1;

    // Default value for the mask, meaning "all bits on"
	pipelineDesc.multisample.mask = ~0u;

    // Default value as well (irrelevant for count = 1 anyways)
	pipelineDesc.multisample.alphaToCoverageEnabled = false;

	// We have a single bind group layout
    wgpu::PipelineLayoutDescriptor pipelineLayoutDesc{};
    pipelineLayoutDesc.nextInChain = nullptr;
	pipelineLayoutDesc.bindGroupLayoutCount = 1;
	pipelineLayoutDesc.bindGroupLayouts = &bindGroupLayout;

    mLayout = device.CreatePipelineLayout(&pipelineLayoutDesc);

    // Assign the PipelineLayout to the RenderPipelineDescriptor's layout field
	pipelineDesc.layout = mLayout;

    mHandle = device.CreateRenderPipeline(&pipelineDesc);
    if (mHandle == nullptr) {
        std::cerr << "Render pipeline creation failed!" << std::endl;
        return false;
    }

    return true;
}

void RenderPipeline::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
