#include "ShaderModule.h"

#include <fstream>
#include <iostream>

DAWN_BEGIN_NAMESPACE

ShaderModule::~ShaderModule()
{
    destroy();
}

bool ShaderModule::loadFromFile(const wgpu::Device& device, const char* filename)
{
    destroy();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        assert(0);
		return false;
	}

    file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	std::string shaderSource(size, ' ');
	file.seekg(0);
	file.read(shaderSource.data(), size);

    wgpu::ShaderModuleWGSLDescriptor shaderCodeDesc{};
	shaderCodeDesc.code = shaderSource.c_str();

    wgpu::ShaderModuleDescriptor shaderModuleDescriptor{};
    shaderModuleDescriptor.nextInChain = &shaderCodeDesc;

    mHandle = device.CreateShaderModule(&shaderModuleDescriptor);
    if (mHandle == nullptr) {
        std::cerr << "Shader module creation failed!" << std::endl;
        assert(0);
        return false;
    }

    return true;
}

void ShaderModule::destroy()
{
    mHandle = nullptr;
}

DAWN_END_NAMESPACE
