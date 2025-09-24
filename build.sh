#!/bin/bash

Date=$(date +"%Y-%m-%d")

########
# Debug
########

# Create the target directories first
mkdir -p releases/Debug/include/webgpu
mkdir -p releases/Debug/include/dawn

# Copy the contents recursively, overwriting if needed
cp -rf dawn/include/webgpu/* releases/Debug/include/webgpu/
cp -rf dawn/out/Debug/gen/include/dawn/* releases/Debug/include/dawn/
cp -rf dawn/out/Debug/gen/include/webgpu/* releases/Debug/include/webgpu/

# Ensure target directory exists
mkdir -p releases/Debug/lib

# Copy the file, overwriting if it exists
cp -f dawn/out/Debug/src/dawn/native/libwebgpu_dawn.so releases/Debug/lib/

# Create zip archive
# Go into the folder, then zip contents so the folder itself is not included
(cd releases/Debug && zip -r "../dawn_debug_${Date}_linux_x64.zip" ./*)

#########
# Release
#########

# Create the target directories first
mkdir -p releases/Release/include/webgpu
mkdir -p releases/Release/include/dawn

# Copy the contents recursively, overwriting if needed
cp -rf dawn/include/webgpu/* releases/Release/include/webgpu/
cp -rf dawn/out/Release/gen/include/dawn/* releases/Release/include/dawn/
cp -rf dawn/out/Release/gen/include/webgpu/* releases/Release/include/webgpu/

# Ensure target directory exists
mkdir -p releases/Release/lib

# Copy the file, overwriting if it exists
cp -f dawn/out/Release/src/dawn/native/libwebgpu_dawn.so releases/Release/lib/

# Create zip archive
# Go into the folder, then zip contents so the folder itself is not included
(cd releases/Release && zip -r "../dawn_release_${Date}_linux_x64.zip" ./*)


