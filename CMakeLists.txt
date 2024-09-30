cmake_minimum_required(VERSION 3.16.0)
project(gstreamer_demo VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Also you can import only required components, like so
# find_package(GStreamer REQUIRED COMPONENTS gstbase gstreamer-1.0)
# gstbase - for custom elements
# gstreamer-1.0 - multimedia processing capabilities
find_package(GStreamer REQUIRED)

include_directories(
    inc
    ${GSTREAMER_INCLUDE_DIRS}
)

add_subdirectory(3rdparty/spdlog)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    ${GSTREAMER_LIBRARIES}
)
