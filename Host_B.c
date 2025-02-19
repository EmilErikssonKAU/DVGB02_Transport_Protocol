#include <stdbool.h>
#include <string.h>
#include "Sim_Engine.h"
#include "Host_helpfunctions.h"

#define B 1

// Global variables
bool seqnumber;

/* Function that creates a packet, containing provided text and seqnumber */
struct pkt makepkt(char *payload, int seqnumber)
{
  struct pkt packet;

  // If packet is ACK
  if (strcmp(payload, "ACK") == 0)
  {
    strcpy(packet.payload, payload);
    packet.seqnum = -1;
    packet.acknum = seqnumber;
  }

  // If packet isn't ACK
  else
  {
    /* DON'T IMPLEMENT */
  }

  // Set checksum
  packet.checksum = getCheckSum(packet);

  // return packet
  return packet;
}

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init()
{
  seqnumber = 0;
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet)
{
  // If not corrupt and correct sequencenumber
  if (notcorrupt(packet) && correctSeqnumber(packet, seqnumber))
  {
    tolayer5(B, packet.payload);
    tolayer3(B, makepkt("ACK", seqnumber));
    seqnumber = nextSeqNumber(seqnumber);
  }

  // If not corrupt and incorrect sequencenumber
  else if (notcorrupt(packet) && !correctSeqnumber(packet, seqnumber))
  {
    tolayer3(B, makepkt("ACK", seqnumber));
  }

  // If corrupt
  else if (!notcorrupt(packet))
  {
    printf("Packet is corrupt!\n");
  }
}

/* Called from layer 5, passed the data to be sent to other side */
void B_output(struct msg message)
{
  /* DON'T IMPLEMENT */
}

/* Called when B's timer goes off */
void B_timerinterrupt()
{
  /* DON'T IMPLEMENT */
}
