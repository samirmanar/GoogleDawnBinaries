
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DAWN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/dawn)

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
    ${CMAKE_SOURCE_DIR}/package/$<CONFIG>/include
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/package/$<CONFIG>/lib/webgpu_dawn.lib
    SDL3::SDL3
)


set(DAWN_RUNTIME_LIB ${CMAKE_SOURCE_DIR}/package/$<CONFIG>/bin/webgpu_dawn.dll)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying '${DAWN_RUNTIME_LIB}' to '$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>'..."
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${DAWN_RUNTIME_LIB}
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
)

message("------------------------------------------------------------------------------")
message(" Debug Info:")
message("   CMAKE_BUILD_TYPE:  " ${CMAKE_BUILD_TYPE})
message("   CMAKE_BINARY_DIR:  " ${CMAKE_BINARY_DIR})
message("   DAWN_INCLUDE_DIRS: " ${DAWN_INCLUDE_DIRS})
message("   DAWN_RUNTIME_LIB: " ${DAWN_RUNTIME_LIB})
message("   glm_INCLUDE_DIR:   " ${glm_INCLUDE_DIR})
message("------------------------------------------------------------------------------")
