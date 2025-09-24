include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)

# SDL3
if (NOT TARGET SDL3)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY  https://github.com/libsdl-org/SDL
        GIT_TAG         735f0cc300ab1fd5fb150f1d16a0928adc65bb2f
        GIT_PROGRESS    TRUE
    )
    FetchContent_MakeAvailable(SDL3)
endif()

# glm
if (NOT TARGET glm)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm
        GIT_TAG         2d4c4b4dd31fde06cfffad7915c2b3006402322f
        GIT_PROGRESS    TRUE
    )
    FetchContent_MakeAvailable(glm)
    set(glm_INCLUDE_DIR ${glm_SOURCE_DIR} PARENT_SCOPE)
endif()

# Dawn
if(WIN32)

    if (NOT TARGET dawn_debug)
        # dawn_debug
        FetchContent_Declare(dawn_debug
        URL https://github.com/samirmanar/GoogleDawnBinaries/releases/download/2025-09-23/dawn_debug_2025-09-23_win_x64.zip
        GIT_PROGRESS TRUE
        )
        FetchContent_MakeAvailable(dawn_debug)
        set(Dawn_Debug_DIR ${dawn_debug_SOURCE_DIR})
    endif()

    if (NOT TARGET dawn_release)
        # dawn_release
        FetchContent_Declare(dawn_release
        URL https://github.com/samirmanar/GoogleDawnBinaries/releases/download/2025-09-23/dawn_release_2025-09-23_win_x64.zip
        GIT_PROGRESS TRUE
        )
        FetchContent_MakeAvailable(dawn_release)
        set(Dawn_Release_DIR ${dawn_release_SOURCE_DIR})
    endif()
    
    set(Dawn_DIR "$<IF:$<CONFIG:Debug>,${Dawn_Debug_DIR},${Dawn_Release_DIR}>")
    set(Dawn_INCLUDE_DIR ${Dawn_DIR}/include PARENT_SCOPE)
    set(Dawn_LIBRARY ${Dawn_DIR}/lib/webgpu_dawn.lib PARENT_SCOPE)
    set(DAWN_RUNTIME_LIB ${Dawn_DIR}/bin/webgpu_dawn.dll PARENT_SCOPE)

elseif(UNIX AND NOT APPLE)

    if (NOT TARGET dawn_debug)
        # dawn_debug
        FetchContent_Declare(dawn_debug
        URL https://github.com/samirmanar/GoogleDawnBinaries/releases/download/2025-09-23/dawn_debug_2025-09-23_linux_x64.zip
        GIT_PROGRESS TRUE
        )
        FetchContent_MakeAvailable(dawn_debug)
        set(Dawn_Debug_DIR ${dawn_debug_SOURCE_DIR})
    endif()

    if (NOT TARGET dawn_release)
        # dawn_release
        FetchContent_Declare(dawn_release
        URL https://github.com/samirmanar/GoogleDawnBinaries/releases/download/2025-09-23/dawn_release_2025-09-23_linux_x64.zip
        GIT_PROGRESS TRUE
        )
        FetchContent_MakeAvailable(dawn_release)
        set(Dawn_Release_DIR ${dawn_release_SOURCE_DIR})
    endif()

    set(Dawn_DIR "$<IF:$<CONFIG:Debug>,${Dawn_Debug_DIR},${Dawn_Release_DIR}>")
    set(Dawn_INCLUDE_DIR ${Dawn_DIR}/include PARENT_SCOPE)
    set(Dawn_LIBRARY ${Dawn_DIR}/lib/libwebgpu_dawn.so PARENT_SCOPE)

endif()
