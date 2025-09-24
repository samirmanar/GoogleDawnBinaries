#include "Device.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

Device::~Device()
{
    destroy();
}

bool Device::create(wgpu::Adapter adapter)
{
    destroy();

    wgpu::DeviceDescriptor deviceDesc = {};
    deviceDesc.SetDeviceLostCallback(
        wgpu::CallbackMode::AllowSpontaneous,
        [](const wgpu::Device&, wgpu::DeviceLostReason reason, wgpu::StringView message) {
            const char* reasonName = "";
            switch (reason) {
            case wgpu::DeviceLostReason::Unknown:
                reasonName = "Unknown";
                break;
            case wgpu::DeviceLostReason::Destroyed:
                reasonName = "Destroyed";
                break;
            case wgpu::DeviceLostReason::CallbackCancelled:
                reasonName = "Callback Cancelled";
                break;
            case wgpu::DeviceLostReason::FailedCreation:
                reasonName = "Failed Creation";
                break;
            default:
                assert(0);
            }
            std::cerr << "Device lost because of " << reasonName << ": " << message.data;
        });

    deviceDesc.SetUncapturedErrorCallback([](const wgpu::Device& device,
        wgpu::ErrorType type,
        wgpu::StringView message) {
            std::cerr << "Error type " << (int)type << ": " << message.data;
        });

    mHandle = adapter.CreateDevice(&deviceDesc);
    if (!mHandle) {
        std::cerr << "Failed to create device!" << std::endl;
        assert(0);
        return false;
    }

    mQueue = mHandle.GetQueue();

    return true;
}

void Device::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
