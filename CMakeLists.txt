cmake_minimum_required(VERSION 3.10)

project("fractals")

set(TARGET_NAME app_${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_SOURCE_DIR}/cmake/SetupSFML.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CustomCommands.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CompilerOptions.cmake)

file(GLOB_RECURSE SOURCE_FILES
    src/*.cpp
)

file(GLOB_RECURSE HEADER_FILES
    include/*.h
)

add_executable(${TARGET_NAME}
    main.cpp
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_DIR}/include
)

target_compile_options(${TARGET_NAME} PRIVATE
    ${COMMON_COMPILE_OPTIONS}
    ${COMMON_ERROR_OPTIONS}
)

# Link SFML libraries
target_link_libraries(${TARGET_NAME} PRIVATE
    ${SANITIZER_FLAGS}
    sfml-graphics sfml-window sfml-system
)
