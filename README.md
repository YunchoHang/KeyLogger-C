# **X11 Keylogger**

A minimal keylogger built using the X11 library to capture and log keyboard inputs on Linux systems. The logged keys are stored in a file (`keylog.txt`) for analysis or debugging purposes.

## **Features**
- Captures and logs keypress events on Linux systems.
- Writes keystrokes to a file (`keylog.txt`) in real-time.
- Graceful shutdown with signal handling (e.g., `Ctrl+C`).

---

## **Prerequisites**
- A Linux-based operating system.
- **X11** development libraries installed.
- **gcc** or any compatible C compiler.

To install the necessary libraries, use the following command (for Ubuntu/Debian-based systems):
```bash
sudo apt-get install libx11-dev
```

---

## **Installation**
1. Clone this repository or copy the source code:
   ```bash
   git clone https://github.com/YunchoHang/KeyLogger-C.git
   cd KeyLogger-C
   ```

2. Compile the code using `gcc`:
   ```bash
   gcc -o keylogger keylogger.c -lX11
   ```

3. Run the program:
   ```bash
   ./keylogger
   ```

---

## **How It Works**
1. **Keyboard Input Capture**  
   The program uses X11 functions to grab the keyboard and listen for keypress events.

2. **Logging**  
   Each keypress is logged into a file named `keylog.txt`. The file is updated in real-time.

3. **Graceful Exit**  
   The program handles `SIGINT` (Ctrl+C) and `SIGTERM` signals to ensure resources (e.g., file and display) are properly released upon termination.

---

## **Usage**
- Start the keylogger:
   ```bash
   ./keylogger
   ```
- The keystrokes will be logged in `keylog.txt`.
- Stop the program by pressing `Ctrl+C`.

---

## **Code Highlights**
- **Signal Handling**  
  Ensures the program exits gracefully when interrupted.
  ```c
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);
  ```

- **X11 Integration**  
  Captures keypress events using the X11 library:
  ```c
  XSelectInput(display, root, KeyPressMask | KeyReleaseMask);
  XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
  ```

- **Logging Functionality**  
  Logs keystrokes to a file in real-time:
  ```c
  void log_key(const char *key) {
      if (file != NULL) {
          fprintf(file, "%s\n", key);
          fflush(file);
      }
  }
  ```

---

## **Limitations**
- This program requires root privileges to grab the keyboard input on most Linux systems.
- Only works on systems using X11 (does not support Wayland).

---

## **Disclaimer**
This project is for educational purposes only. Unauthorized use of keyloggers can violate privacy laws. Always obtain proper consent before running this program.

---
