# Google Dawn Binaries

## How to build Dawn

### Debug

```bash
cmake -S . -B ./out/Debug                        ^
-G Ninja                                         ^
-D CMAKE_BUILD_TYPE=Debug                        ^
-D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug ^
-D ABSL_MSVC_STATIC_RUNTIME=ON                   ^
-D DAWN_BUILD_SAMPLES=OFF                        ^
-D DAWN_BUILD_TESTS=OFF                          ^
-D DAWN_ENABLE_D3D12=ON                          ^
-D DAWN_ENABLE_D3D11=OFF                         ^
-D DAWN_ENABLE_NULL=OFF                          ^
-D DAWN_ENABLE_DESKTOP_GL=OFF                    ^
-D DAWN_ENABLE_OPENGLES=OFF                      ^
-D DAWN_ENABLE_VULKAN=OFF                        ^
-D DAWN_USE_GLFW=OFF                             ^
-D DAWN_ENABLE_SPIRV_VALIDATION=OFF              ^
-D DAWN_DXC_ENABLE_ASSERTS_IN_NDEBUG=OFF         ^
-D DAWN_FETCH_DEPENDENCIES=OFF                   ^
-D DAWN_BUILD_MONOLITHIC_LIBRARY=SHARED          ^
-D TINT_BUILD_TESTS=OFF                          ^
-D TINT_BUILD_SPV_READER=ON                      ^
-D TINT_BUILD_SPV_WRITER=ON                      ^
-D TINT_BUILD_CMD_TOOLS=ON                       ^
-D DAWN_FORCE_SYSTEM_COMPONENT_LOAD=ON
   
cmake --build ./out/Debug --target webgpu_dawn
```

### Release

```bash
cmake -S . -B ./out/Release                 ^
-G Ninja                                    ^
-D CMAKE_BUILD_TYPE=Release                 ^
-D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded ^
-D ABSL_MSVC_STATIC_RUNTIME=ON              ^
-D DAWN_BUILD_SAMPLES=OFF                   ^
-D DAWN_BUILD_TESTS=OFF                     ^
-D DAWN_ENABLE_D3D12=ON                     ^
-D DAWN_ENABLE_D3D11=OFF                    ^
-D DAWN_ENABLE_NULL=OFF                     ^
-D DAWN_ENABLE_DESKTOP_GL=OFF               ^
-D DAWN_ENABLE_OPENGLES=OFF                 ^
-D DAWN_ENABLE_VULKAN=OFF                   ^
-D DAWN_USE_GLFW=OFF                        ^
-D DAWN_ENABLE_SPIRV_VALIDATION=OFF         ^
-D DAWN_DXC_ENABLE_ASSERTS_IN_NDEBUG=OFF    ^
-D DAWN_FETCH_DEPENDENCIES=OFF              ^
-D DAWN_BUILD_MONOLITHIC_LIBRARY=SHARED     ^
-D TINT_BUILD_TESTS=OFF                     ^
-D TINT_BUILD_SPV_READER=ON                 ^
-D TINT_BUILD_SPV_WRITER=ON                 ^
-D TINT_BUILD_CMD_TOOLS=ON                  ^
-D DAWN_FORCE_SYSTEM_COMPONENT_LOAD=ON
   
cmake --build ./out/Release --target webgpu_dawn
```

## How to build the demo project

### Debug
```bash
cmake -S . -B ./build
cmake --build ./build --config Debug
```

### Release
```bash
cmake -S . -B ./build
cmake --build ./build --config Release
```
