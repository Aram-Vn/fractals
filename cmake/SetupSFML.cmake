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
