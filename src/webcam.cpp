#include "essentials.h"
#include "errors.h"

#include "webcam.h"

int WebCamStream::execWithBus() {
    return 0;
}

namespace {

// Callback function to handle messages from the bus
/*static void bus_message_handler(GstBus *bus, GstMessage *msg, gpointer data) {
    // also there is GST_MESSAGE_WARNING, GST_MESSAGE_INFO, GST_MESSAGE_STATE_CHANGED
    // GST_MESSAGE_BUFFERING (with percentage), GST_MESSAGE_CLOCK_LOST,
    // GST_MESSAGE_TAG (title, artist, genre etc),
    // GST_MESSAGE_DURATION_CHANGED (if duration recalculated),
    // GST_MESSAGE_LATENCY (to adjust latency dynamically)
    // GST_MESSAGE_ASYNC_DONE (for continious status changes)
    // GST_MESSAGE_ELEMENT (specific notifications or events by individual elements)

    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            g_print("End of stream reached.\n");
            g_main_loop_quit((GMainLoop *)data); // Stop the main loop
            break;
        case GST_MESSAGE_ERROR: {
            GError *err;
            gchar *debug_info;
            gst_message_parse_error(msg, &err, &debug_info);
            g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
            g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
            g_error_free(err);
            g_free(debug_info);
            g_main_loop_quit((GMainLoop *)data); // Stop the main loop
            break;
        }
        default:
            break;
    }
}*/

} // anonymous namespace

int WebCamStream::execWithoutBus() {
    spdlog::info("test without bus stated");

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
    GstElement
        *pipeline = gst_pipeline_new("webcam-pipeline"), // webcam-pipeline is just a name
        *source = gst_element_factory_make("v4l2src", "source"), // For Linux
        *convert = gst_element_factory_make("videoconvert", "convert"), // look up
        *sink = gst_element_factory_make("autovideosink", "video_sink");

    /* Converting
        If your sink doesn't support pixel format / color space, you may use 'videoconvert' element
        Omitting it reduces overhead

        For now, it is required
        TODO: try to exclude convert
    */

    /* If you need to process frames via your application, see "appsink"
        It could be used in pair with video_sink, but it is not present there
        to make an example simplier
    */

    if (!pipeline || !source || !convert || !sink) {
        // TODO: with custom formatter you can exclude reinterpert_cast

        spdlog::error("Failed to prepare all gst elements, {} {} {} {}",
            static_cast<void *>(pipeline),
            static_cast<void *>(source),
            static_cast<void *>(convert),
            static_cast<void *>(sink));
        return ERR_SYSTEM_GST;
    }

    // If you have multiple devices, you can define it manually, or autoselect vould start
    // g_object_set(source, "device", "/dev/video0", NULL);

    /* we use GST_BIN, it casts object to GstBin* type
        'GstBin' is a type of 'GstElement', that can contain other 'GstElement'
    */
    gst_bin_add_many(GST_BIN(pipeline), source, convert, sink, NULL);
    int rc = gst_element_link_many(source, convert, sink, NULL);
    if(!rc) {
        spdlog::error("GST object link error");
        return ERR_SYSTEM_GST;
    }

    // Start the pipeline
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Wait until error or End-Of-Stream
    // 1. Hang application until EOS (Forever, easiest method)
    GstBus *bus = gst_element_get_bus(pipeline);
    gst_bus_poll(bus, GST_MESSAGE_EOS, GST_CLOCK_TIME_NONE);
    gst_object_unref(bus);

    // Free resources
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    /* 2. Set the timeout
        GstBus *bus = gst_element_get_bus(pipeline);
        GstMessage *msg = gst_bus_timed_pop(bus, 5000000000); // 5 seconds timeout
        if (msg != NULL) {
            // Handle the message (e.g., check if it's EOS)
            gst_message_unref(msg);
        } else {
            // Handle timeout (e.g., log a message or exit)
            g_print("Timeout waiting for EOS message.\n");
        }
        gst_object_unref(bus);
    */
   /* 3. Use main loop
        Uses GStreamer main loop, it's a common approach,
        allows to handle messages without blocking the main thread
        <look at bus_message_handler>

        // Create a main loop
        GMainLoop *loop = g_main_loop_new(NULL, FALSE);
        GstBus *bus = gst_element_get_bus(pipeline);

        // Add a watch to the bus to handle messages
        gst_bus_add_watch(bus, bus_message_handler, loop);

        // Start the main loop
        g_main_loop_run(loop);

        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(bus);
        gst_object_unref(pipeline);
        g_main_loop_unref(loop);
   */

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