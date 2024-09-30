#include "essentials.h"

#include <iostream>

#define ERR_USER -1000
#define ERR_USER_INVALID_INPUT -1001 // User selected wrong value

#define ERR_TYPE_LEN 1000
#define ERR_IS_TYPE(type, value) ((type >= value) && ((type - ERR_TYPE_LEN) < value)))

int main(int argc, char *argv[]) {
    spdlog::set_pattern("[%m/%d %H:%M:%S] %v");
    spdlog::info("gstreamer_demo is launching");

    // GStreamer Initialization
    gst_init(&argc, &argv);

    std::cout << "Select example:\n1. Webcam\n2. Video player\n3. Audio player\n4. Recorder\n>> ";
    int value;
    std::cin >> value;

    enum class MenuEntry {
        WEBCAM = 1,
        VIDEOPLAYER,
        AUDIOPLAYER,
        RECORDER,
    };

    int rc = 0;
    switch(static_cast<MenuEntry>(value)) {
        case MenuEntry::WEBCAM:
            //webCam();
            break;
        case MenuEntry::VIDEOPLAYER:
            //videoPlayer();
            break;
        case MenuEntry::AUDIOPLAYER:
            //audioPlayer();
            break;
        case MenuEntry::RECORDER:
            //recorder();
            break;
        default:
            spdlog::critical("Invalid menu selection, {}", value);
            rc = ERR_USER_INVALID_INPUT;
            break;
    }

    spdlog::info("Exiting app");
    return rc ? EXIT_FAILURE : EXIT_SUCCESS;
}