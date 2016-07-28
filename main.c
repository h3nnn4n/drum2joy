#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE  "/dev/snd/midiC1D0"

int main(void) {
   unsigned char inpacket[4];

   // first open the sequencer device for reading.
   int seqfd = open(MIDI_DEVICE, O_RDONLY);
   if (seqfd == -1) {
      printf("Error: cannot open %s\n", MIDI_DEVICE);
      exit(1);
   }

   // now just wait around for MIDI bytes to arrive and print them to screen.
   while (1) {
      read(seqfd, &inpacket, sizeof(inpacket));

      // print the MIDI byte if this input packet contains one
      if (inpacket[0] == SEQ_MIDIPUTC) {
         printf("received MIDI byte: %d\n", inpacket[1]);
      }
   }

   return 0;
}
