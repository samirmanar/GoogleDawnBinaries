#include "Instance.h"

#include <iostream>

DAWN_BEGIN_NAMESPACE

Instance::~Instance()
{
	destroy();
}

bool Instance::create()
{
    destroy();

    wgpu::InstanceDescriptor instanceDescriptor{};
    mHandle = wgpu::CreateInstance(&instanceDescriptor);
    if (mHandle == nullptr) {
        std::cerr << "Instance creation failed!\n";
        assert(0);
        return false;
    }

    return true;
}

void Instance::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
