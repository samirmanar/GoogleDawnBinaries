#include <iostream>

#include <webgpu/webgpu_cpp.h>

#include <SDL3/SDL.h>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Fps.h"
#include "Helpers.h"
#include "Instance.h"
#include "Adapter.h"
#include "Device.h"
#include "Surface.h"
#include "Buffer.h"
#include "ShaderModule.h"
#include "BindGroupLayout.h"
#include "BindGroup.h"
#include "RenderPipeline.h"
#include "CommandEncoder.h"
#include "RenderPass.h"

int main(int argc, char* argv[])
{
    bool bSuccess;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    const int kWidth = 640;
    const int kHeight = 480;

    SDL_Window* window = SDL_CreateWindow("Google Dawn + SDL3 + GLM", kWidth, kHeight, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Couldn't create SDL3 window: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    dawn::Instance instance;
    bSuccess = instance.create();
    assert(bSuccess);

    dawn::Adapter adapter;
    bSuccess = adapter.create(instance);
    assert(bSuccess);
    adapter.printInfo();

    dawn::Device device;
    bSuccess = device.create(adapter);
    assert(bSuccess);

    auto queue = device.getQueue();

    dawn::Surface surface;
    bSuccess = surface.create(instance, window);
    assert(bSuccess);
    surface.configure(adapter, device, kWidth, kHeight);

    struct Uniforms {
        alignas(16) glm::mat4 m;
        alignas(16) glm::mat4 v;
        alignas(16) glm::mat4 p;
        alignas(16) glm::vec3 lightPos;
        alignas(16) glm::vec3 cameraPos;
    } uniforms;

    dawn::Buffer uniformBuffer;
    size_t uniformBufferSize = alignBufferSize(sizeof(uniforms), 16);    // buffer size needs to be aligned to 16 bytes
    bSuccess = uniformBuffer.create(device, wgpu::BufferUsage::Uniform | wgpu::BufferUsage::CopyDst, uniformBufferSize);
    assert(bSuccess);

    // Model matrix
    uniforms.m = glm::mat4(1.0);

    // View matrix
    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    uniforms.v = glm::lookAt(eye, center, up);

    // Projection matrix
    uniforms.p = glm::perspective(glm::radians(45.0f), kWidth / (float)kHeight, 1.0f, 1000.0f);

    uniforms.lightPos = glm::vec3(0.0f, 0.0f, 3.0f);
    uniforms.cameraPos = eye;

    // Vertex positions
    static const float positions[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    // Vertex colors
    static const float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    // Vertex normals
    static const float normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    static const uint32_t indices[] = {
        0, 1, 2,
    };

    dawn::Buffer positionBuffer;
    size_t positionBufferSize = alignBufferSize(sizeof(positions), 16);    // buffer size needs to be aligned to 16 bytes
    bSuccess = positionBuffer.create(device, wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, positionBufferSize, positions);
    assert(bSuccess);

    dawn::Buffer colorBuffer;
    size_t colorBufferSize = alignBufferSize(sizeof(colors), 16);    // buffer size needs to be aligned to 16 bytes
    bSuccess = colorBuffer.create(device, wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, colorBufferSize, colors);
    assert(bSuccess);

    dawn::Buffer normalBuffer;
    size_t normalBufferSize = alignBufferSize(sizeof(normals), 16);    // buffer size needs to be aligned to 16 bytes
    bSuccess = normalBuffer.create(device, wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, normalBufferSize, normals);
    assert(bSuccess);

    dawn::Buffer indexBuffer;
    size_t indexBufferSize = alignBufferSize(sizeof(indices), 4);    // buffer size needs to be aligned to 4 bytes
    bSuccess = indexBuffer.create(device, wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst, indexBufferSize, indices);
    assert(bSuccess);

    dawn::ShaderModule module;
    bSuccess = module.loadFromFile(device, "../../resources/shader.wgsl");
    assert(bSuccess);

    dawn::BindGroupLayout bindGroupLayout;
    bSuccess = bindGroupLayout.create(device, uniformBufferSize);
    assert(bSuccess);

    dawn::BindGroup bindGroup;
    bSuccess = bindGroup.create(device, bindGroupLayout, uniformBuffer, uniformBufferSize);
    assert(bSuccess);

    dawn::RenderPipeline pipeline;
    bSuccess = pipeline.create(device, module, bindGroupLayout, surface.getPreferredSurfaceTextureFormat());
    assert(bSuccess);

    dawn::CommandEncoder encoder;

    bool bRunning = true;

    Fps fps;

    auto startTime = std::chrono::high_resolution_clock::now();

    while (bRunning) {

        SDL_Event event;
        // Process all pending events before rendering
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                bRunning = false;
                break;
            default:
                break;
            }
        }

        if (!bRunning)
            break;

        auto now = std::chrono::high_resolution_clock::now();
        float elapsed = (float)(std::chrono::duration<double, std::milli>(now - startTime).count());

        constexpr float SPEED = 0.2f;
        constexpr float AMPLITUDE_RADIANS = 1.2f;

        float time = static_cast<float>(elapsed) * SPEED;
        uniforms.m = glm::rotate(glm::mat4(1.0), (float)sin(glm::radians(time)) * AMPLITUDE_RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));

        uniformBuffer.write(queue, &uniforms, uniformBufferSize);

        wgpu::SurfaceTexture surfaceTexture;
        surface.getCurrentTexture(&surfaceTexture);

        wgpu::TextureView textureView = surfaceTexture.texture.CreateView();

        bSuccess = encoder.create(device);
        assert(bSuccess);

        dawn::RenderPass pass;
        pass.begin(textureView, encoder);

        pass.setPipeline(pipeline);

        pass.setVertexBuffer(positionBuffer, 0);
        pass.setVertexBuffer(colorBuffer, 1);
        pass.setVertexBuffer(normalBuffer, 2);

        pass.setIndexBuffer(indexBuffer, 0);

        pass.setBindGroup(0, bindGroup);

        int numIndices = sizeof(indices) / sizeof(indices[0]);
        pass.drawIndexed(numIndices);

        pass.end();

        wgpu::CommandBuffer commands = encoder.finish();

        queue.Submit(1, &commands);

        surface.present();

        if (fps.onFrame()) {
            std::cout << std::format("FPS: {:.2f}, MS: {:.2f}\n", fps.getFPS(), fps.getMS());
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
