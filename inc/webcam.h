#ifndef _WEBCAM_H_
#define _WEBCAM_H_

class WebCamStream {
public:
    // Basic (but working) example
    int execWithoutBus();

    /*
     Bus allows to handle EOS (End of Stream), Handle errors, Manage Resources:
     via State Management (GST_STATE_PLAYING, GST_STATE_PAUSED)
      - Releasing resources when the pipeline is paused.
      - Allocating resources when the pipeline is playing;
     Dynamic Pipeline Changes
     In more complex applications, you might want to change the pipeline dynamically
      (e.g., adding or removing elements). The bus can help you manage these changes by
      notifying you of the current state of the pipeline and any issues that
      arise during these modifications.
     Avoiding Resource Leaks
      By monitoring the bus for EOS and error messages,
      you can ensure that you properly clean up resources when they are no longer needed.
      For example, if you receive an EOS message, you can stop the pipeline and free any
      resources associated with it, preventing memory leaks.
    */
    int execWithBus();
};

int callWebCamDemo();

#endif // _WEBCAM_H_