#include "essentials.h"
#include "errors.h"

#include "webcam.h"

int WebCamStream::execWithBus() {
    return 0;
}

int WebCamStream::execWithoutBus() {
    spdlog::info("test without bus stated");

    GstElement *pipeline;
    GstElement *source;

    /*
     "sink" is an element, that receives data from a pipeline
     and typically outputs it to a destination

     Types:
        - Video Sinks (
            autovideosink - "Automatic selection: X11, Wayland, Windows, etc"
            ximagesink - X11 Linux
            glimagesink - OpenGL
            etc.
        )
        - Audio Sinks (autoaudiosinkl, alsasink, pulsesink, etc)
        - File Sinks (
            filesink - writes data to file
            multifilesink - writes to multiple files, useful for
                streams with multiple channels
        )
        - Network Sinks (
            udpsink - over UDP to specified address and port
            tcpsink - over TCP to specified address and port
        )
    */
    GstElement *sink;

    return 0;
}

int callWebCamDemo() {
    spdlog::set_pattern("[%m/%d %H:%M:%S] [WebCam] %v");

    std::cout << "Select example:\n1. With Bus\n2. Without Bus\n>> ";
    int value;
    std::cin >> value;

    enum class MenuEntry {
        WITH_BUS = 1,
        WITHOUT_BUS = 2,
    };

    int rc = 0;
    switch(static_cast<MenuEntry>(value)) {
        case MenuEntry::WITH_BUS: {
            WebCamStream stream;
            rc = stream.execWithBus();
            break;
        }
        case MenuEntry::WITHOUT_BUS: {
            WebCamStream stream;
            rc = stream.execWithoutBus();
            break;
        }
        default: {
            spdlog::critical("Invalid menu selection, {}", value);
            rc = ERR_USER_INVALID_INPUT;
            break;
        }
    }

    if(rc) {
        spdlog::error("Test returned an error, {}", rc);
    } else {
        spdlog::info("Test performed succesfully");
    }

    spdlog::set_pattern("[%m/%d %H:%M:%S] %v");
    return rc;
}