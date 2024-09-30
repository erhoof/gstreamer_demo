# FindGStreamer.cmake
# Locate GStreamer libraries and include directories

# Set the required version
find_package(PkgConfig REQUIRED)

# Find GStreamer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GSTREAMER_BASE REQUIRED gstreamer-base-1.0)

# Include directories
include_directories(${GSTREAMER_INCLUDE_DIRS} ${GSTREAMER_BASE_INCLUDE_DIRS})

# Set the GStreamer libraries
set(GSTREAMER_LIBRARIES ${GSTREAMER_LIBRARIES} ${GSTREAMER_BASE_LIBRARIES})

# Provide the results
if (GSTREAMER_FOUND)
    message(STATUS "Found GStreamer: ${GSTREAMER_VERSION}")
else()
    message(FATAL_ERROR "GStreamer not found")
endif()
