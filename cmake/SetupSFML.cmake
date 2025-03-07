# Ensure SFML submodule is initialized and at the correct version
find_package(Git REQUIRED)

execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_SUBMODULE_RESULT
)

if(GIT_SUBMODULE_RESULT)
    message(FATAL_ERROR "Failed to initialize submodules. Please check your internet connection.")
endif()

# Ensure SFML is at the correct version
execute_process(
    COMMAND ${GIT_EXECUTABLE} -C external/SFML checkout 2.5.1
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_CHECKOUT_RESULT
)

if(GIT_CHECKOUT_RESULT)
    message(FATAL_ERROR "Failed to checkout SFML 2.5.1. Please check your repository.")
endif()

# Add SFML as a subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/external/SFML)

find_library(SFML_GRAPHICS_LIBRARY NAMES sfml-graphics PATHS ${CMAKE_SOURCE_DIR}/external/SFML/lib)
find_library(SFML_WINDOW_LIBRARY NAMES sfml-window PATHS ${CMAKE_SOURCE_DIR}/external/SFML/lib)
find_library(SFML_SYSTEM_LIBRARY NAMES sfml-system PATHS ${CMAKE_SOURCE_DIR}/external/SFML/lib)

if(SFML_GRAPHICS_LIBRARY AND SFML_WINDOW_LIBRARY AND SFML_SYSTEM_LIBRARY)
    message(STATUS "[ V ] SFML shared libraries found, using dynamic linking.")
    set(SFML_STATIC_LIBRARIES OFF)
else()
    message(WARNING "[ X ] SFML shared libraries NOT found, switching to static linking.")
    set(SFML_STATIC_LIBRARIES ON)
endif()

set(SFML_DIR ${CMAKE_SOURCE_DIR}/external/SFML)