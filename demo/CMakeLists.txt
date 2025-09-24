
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Dawn_DIR "$<IF:$<CONFIG:Debug>,${Dawn_Debug_DIR},${Dawn_Release_DIR}>")

if(WIN32)
    set(Dawn_LIBRARY ${Dawn_DIR}/lib/webgpu_dawn.lib)
elseif(UNIX AND NOT APPLE)
    set(Dawn_LIBRARY ${Dawn_DIR}/lib/libwebgpu_dawn.so)
endif()

file(GLOB SRC
    "*.cpp"
    "*.h"
)

file(GLOB SRC_EXTERNAL
    "../external/*.*"
)

file(GLOB SRC_RESOURCES
    "../resources/*.*"
)

source_group("external" FILES ${SRC_EXTERNAL})
source_group("resources" FILES ${SRC_RESOURCES})

add_executable(${CMAKE_PROJECT_NAME}
    ${SRC}
    ${SRC_EXTERNAL}
    ${SRC_RESOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${glm_INCLUDE_DIR}
    ${Dawn_DIR}/include
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    SDL3::SDL3
    ${Dawn_LIBRARY}
)

if(WIN32)
    # Copy webgpu dll next to the executable
    set(DAWN_RUNTIME_LIB ${Dawn_DIR}/bin/webgpu_dawn.dll)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying '${DAWN_RUNTIME_LIB}' to '$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>'..."
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            ${DAWN_RUNTIME_LIB}
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
endif()

message("------------------------------------------------------------------------------")
message(" Debug Info:")
message("   CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
message("   CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})
message("   glm_INCLUDE_DIR:  " ${glm_INCLUDE_DIR})
message("------------------------------------------------------------------------------")
