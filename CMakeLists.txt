cmake_minimum_required(VERSION 3.16.0)
project(gstreamer_demo VERSION 1.0.0 LANGUAGES CXX)

# Submodule dependencies
add_subdirectory(3rdparty/spdlog)

# As some distros (Fedora 41 in my case) does not provide all necessary Find*.cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(SOURCES
    src/webcam.cpp
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

# Also you can import only required components, like so
# find_package(GStreamer REQUIRED COMPONENTS gstbase gstreamer-1.0)
# gstbase - for custom elements
# gstreamer-1.0 - multimedia processing capabilities
find_package(GStreamer REQUIRED)

# There we can use "target_include_directories(${PROJECT_NAME} PUBLIC" or "include_directories"
include_directories(
    inc
    ${GSTREAMER_INCLUDE_DIRS}
)
target_precompile_headers(${PROJECT_NAME} PUBLIC inc/essentials.h)

# As precompile headers does not work with link_libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    ${GSTREAMER_LIBRARIES}
)
