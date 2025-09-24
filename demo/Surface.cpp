#include "Surface.h"

#include <iostream>

#include <SDL3/SDL.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <X11/Xlib.h>
#endif

DAWN_BEGIN_NAMESPACE

Surface::~Surface()
{
	destroy();
}

bool Surface::create(const wgpu::Instance& instance, SDL_Window* window)
{
    destroy();

#if defined(_WIN32)
    HWND hwnd = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
    HINSTANCE hinstance = (HINSTANCE)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, nullptr);

    wgpu::SurfaceDescriptorFromWindowsHWND fromWindowsHWND;
    fromWindowsHWND.hinstance = hinstance;
    fromWindowsHWND.hwnd = hwnd;

    wgpu::SurfaceDescriptor surfaceDescriptor{};
    surfaceDescriptor.nextInChain = &fromWindowsHWND;
    surfaceDescriptor.label = "MySurface";

    mHandle = instance.CreateSurface(&surfaceDescriptor);
    if (!mHandle) {
        std::cerr << "Could not create Windows surface!" << std::endl;
        assert(0);
        return false;
    }
#elif defined(__linux__)
    ::Display* display = (Display*)SDL_GetPointerProperty(
            SDL_GetWindowProperties(window),
            SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
            nullptr);

    ::Window x11Window = (Window)(uintptr_t)SDL_GetNumberProperty(
        SDL_GetWindowProperties(window),
        SDL_PROP_WINDOW_X11_WINDOW_NUMBER,
        0);

    if (!display || !x11Window) {
        std::cerr << "Could not get X11 window/display from SDL!" << std::endl;
        assert(0);
        return false;
    }

    wgpu::SurfaceDescriptorFromXlibWindow fromXlibWindow{};
    fromXlibWindow.display = display;
    fromXlibWindow.window = x11Window;

    wgpu::SurfaceDescriptor surfaceDescriptor{};
    surfaceDescriptor.nextInChain = &fromXlibWindow;
    surfaceDescriptor.label = "MySurface";

    mHandle = instance.CreateSurface(&surfaceDescriptor);
    if (!mHandle) {
        std::cerr << "Could not create X11 surface!" << std::endl;
        assert(0);
        return false;
    }
#endif

    return true;
}

void Surface::destroy()
{
    mHandle = nullptr;
}

void Surface::configure(const wgpu::Adapter& adapter, const wgpu::Device& device, uint32_t width, uint32_t height)
{
    wgpu::SurfaceCapabilities capabilities;
    mHandle.GetCapabilities(adapter, &capabilities);

    wgpu::SurfaceConfiguration config {};
    config.device = device;
    config.format = capabilities.formats[0];
    config.width = width;
    config.height = height;
    config.presentMode = wgpu::PresentMode::Immediate;
    mHandle.Configure(&config);

    mPreferredSurfaceTextureFormat = capabilities.formats[0];
}

void Surface::getCurrentTexture(wgpu::SurfaceTexture* surfaceTexture)
{
    mHandle.GetCurrentTexture(surfaceTexture);
}

void Surface::present()
{
    mHandle.Present();
}

DAWN_END_NAMESPACE
