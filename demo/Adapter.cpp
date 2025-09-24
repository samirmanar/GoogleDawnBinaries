#include "Adapter.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

Adapter::~Adapter()
{
	destroy();
}

bool Adapter::create(wgpu::Instance instance)
{
    destroy();

    wgpu::RequestAdapterOptions options{};
    instance.RequestAdapter(
        &options,
        wgpu::CallbackMode::AllowSpontaneous,
        [&](wgpu::RequestAdapterStatus status, wgpu::Adapter adapter, wgpu::StringView message) {
            if (status == wgpu::RequestAdapterStatus::Success) {
                std::cout << "Adapter acquired!" << std::endl;
                mHandle = adapter;
            }
            else {
                std::cerr << "Failed to acquire adapter: " << message.data << std::endl;
                assert(0);
            }
        }
    );

    if (!mHandle) {
        return false;
    }

    wgpu::AdapterInfo info{};
    mHandle.GetInfo(&info);

    mVendor = info.vendor;
    mArchitecture = info.architecture;
    mDevice = info.device;
    mDescription = info.description;
    mVendorID = info.vendorID;
    mDeviceID = info.deviceID;

    switch (info.adapterType)
    {
    case wgpu::AdapterType::DiscreteGPU:
        mAdapterType = "Discrete GPU";
        break;
    case wgpu::AdapterType::IntegratedGPU:
        mAdapterType = "Integrated GPU";
        break;
    case wgpu::AdapterType::CPU:
        mAdapterType = "CPU";
        break;
    case wgpu::AdapterType::Unknown:
    default:
        mAdapterType = "Unknown";
        break;
    }

    switch (info.backendType)
    {
    case wgpu::BackendType::Null:
        mBackendType = "Null";
        break;
    case wgpu::BackendType::WebGPU:
        mBackendType = "WebGPU";
        break;
    case wgpu::BackendType::D3D11:
        mBackendType = "D3D11";
        break;
    case wgpu::BackendType::D3D12:
        mBackendType = "D3D12";
        break;
    case wgpu::BackendType::Metal:
        mBackendType = "Metal";
        break;
    case wgpu::BackendType::Vulkan:
        mBackendType = "Vulkan";
        break;
    case wgpu::BackendType::OpenGL:
        mBackendType = "OpenGL";
        break;
    case wgpu::BackendType::OpenGLES:
        mBackendType = "OpenGLES";
        break;
    case wgpu::BackendType::Undefined:
    default:
        mBackendType = "Undefined";
        break;
    }

    return true;
}

void Adapter::destroy()
{
    mHandle = nullptr;
}

void Adapter::printInfo()
{
    std::cout << "Type: " << mAdapterType << std::endl;
    std::cout << "Name: " << mDevice << std::endl;
    std::cout << "DeviceID: " << std::hex << mDeviceID << std::dec << std::endl;
    std::cout << "Vendor: " << mVendor << std::endl;
    std::cout << "VendorID: " << std::hex << mVendorID << std::dec << std::endl;
    std::cout << "Architecture: " << mArchitecture << std::endl;
    std::cout << "Driver description: " << mDescription << std::endl;
}

DAWN_END_NAMESPACE
