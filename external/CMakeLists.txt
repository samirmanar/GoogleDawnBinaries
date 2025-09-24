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
