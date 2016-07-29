// MIDI Stuff
#include <fcntl.h>
#include <unistd.h>
#include <sys/soundcard.h>

// C stuff
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// X11 stuff
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#define  MIDI_DEVICE  "/dev/snd/midiC1D0"

/*
 * First byte: 153 means pressed, 137 means released
 * Second byte: Which pad was hit
 * Third byte: Intensity
 * Fourth byte: ???
 *
 */

int main(void) {
    unsigned char inpacket[4];
    Display *display;
    unsigned int keycode;
    display = XOpenDisplay(NULL);

    int seqfd = open(MIDI_DEVICE, O_RDONLY);
    if (seqfd == -1) {
        printf("Error: cannot open %s\n", MIDI_DEVICE);
        exit(1);
    }

    while (1) {
        read(seqfd, &inpacket, sizeof(inpacket));
        if ( inpacket[0] == 153 ) {
            switch ( inpacket[1] ) {
                case 38: // Snare
                    printf("Snare\n");
                    keycode = XKeysymToKeycode(display, XK_M);
                    break;
                case 43: // Floor tom
                    printf("Floor tom\n");
                    keycode = XKeysymToKeycode(display, XK_Z);
                    break;
                case 36: // Kick drum
                    printf("Kick drum\n");
                    keycode = XKeysymToKeycode(display, XK_C);
                    break;
                case 49: // Crash
                    printf("Crash\n");
                    keycode = XKeysymToKeycode(display, XK_S);
                    break;
                default:
                    keycode = 0;
                    break;
            }
            if ( keycode ) {
                XTestGrabControl(display, True);
                XTestFakeKeyEvent(display, keycode, True,  0);
                nanosleep((const struct timespec[]){{0, 20000000L}}, NULL); // Sleeps for 0.02 seconds
                XTestFakeKeyEvent(display, keycode, False, 0);
                XSync(display, False);
                XTestGrabControl(display, False);
            }
        }
        /*printf("received MIDI byte: %d %d %d %d\n", inpacket[0], inpacket[1], inpacket[2], inpacket[3]);*/
    }

    return 0;
}
