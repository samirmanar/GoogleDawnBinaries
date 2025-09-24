#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

#include <string>

DAWN_BEGIN_NAMESPACE

class Adapter
{
public:
    ~Adapter();

    bool create(wgpu::Instance instance);
    void destroy();

    void printInfo();

    operator wgpu::Adapter() {
		return mHandle;
	}

protected:
    wgpu::Adapter mHandle = nullptr;

    std::string mVendor;
    std::string mArchitecture;
    std::string mDevice;
    std::string mDescription;
    std::string mBackendType;
    std::string mAdapterType;
    uint32_t mVendorID = 0;
    uint32_t mDeviceID = 0;
};

DAWN_END_NAMESPACE
