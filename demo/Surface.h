#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

//class GLFWwindow;
struct SDL_Window;

DAWN_BEGIN_NAMESPACE

class Surface
{
public:
	~Surface();

	bool create(const wgpu::Instance& instance, SDL_Window* window);
	void destroy();

	void configure(const wgpu::Adapter& adapter, const wgpu::Device& device, uint32_t width, uint32_t height);

	void getCurrentTexture(wgpu::SurfaceTexture* surfaceTexture);

	void present();

	operator wgpu::Surface() {
		return mHandle;
	}

	wgpu::TextureFormat getPreferredSurfaceTextureFormat() const {
		return mPreferredSurfaceTextureFormat;
	}

protected:
    wgpu::Surface mHandle = nullptr;
	wgpu::TextureFormat mPreferredSurfaceTextureFormat = wgpu::TextureFormat::BGRA8Unorm;

};

DAWN_END_NAMESPACE
