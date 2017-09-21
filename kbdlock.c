#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
    Display *dpy;
    XEvent xevent;
    Window w;
    const char *password = "ubuntu";
    int correct_keys = 0;
    
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Couldn't open X display %s\n",
            XDisplayName(NULL));
        return 1;
    }
    printf("Keyboard Locked!\n");
    // Lock keyboard and mouse
    w = RootWindow(dpy, DefaultScreen(dpy));
    XGrabKeyboard(dpy, w, False,
        GrabModeAsync, GrabModeAsync, CurrentTime);
    /*XGrabPointer(dpy, w, False, 0,
        GrabModeAsync, GrabModeAsync,
        None, None, CurrentTime);*/

    // X Event-handling loop.
    // Look at keypress events and compare them with the password,
    // one letter at a time.
    while (1) {
        XNextEvent(dpy, &xevent);
        if (xevent.type == KeyPress) {
            XKeyEvent *ke = (XKeyEvent *)&xevent;
            KeySym keysym;
            XLookupString(ke, NULL, 0, &keysym, NULL);
            //printf("Got keysym %d, '%c'\n", keysym, keysym);
            if (keysym == password[correct_keys]) {
                correct_keys++;
           //     printf("Correct key pressed\n");
                if (password[correct_keys] == '\0') {
                    printf("Password correct. \n Keyboard Unlocked!\n");
                    break;
                }
            } else {
                correct_keys = 0;
                printf("Keyboard locked, enter password\n");
            }
        }
    }
    XCloseDisplay(dpy);
    return 0;
}

