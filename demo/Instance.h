#pragma once

#include "Namespace.h"

#include <webgpu/webgpu_cpp.h>

DAWN_BEGIN_NAMESPACE

class Instance
{
public:
	~Instance();

	bool create();
	void destroy();

	operator wgpu::Instance() {
		return mHandle;
	}

protected:
	wgpu::Instance mHandle = nullptr;
};

DAWN_END_NAMESPACE
