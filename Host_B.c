#include <stdbool.h>
#include <string.h>
#include "Sim_Engine.h"

// Global variables
bool seqnumber;

/* Function that checks if packet is corrupt */
bool notcorrupt(struct pkt packet)
{
  int sum = 0;

  // Calculate checksum of payload
  for (int i = 0; i < 19; i++)
  {
    sum += packet.payload[i];
  }

  // Inlcude acknum and seqnum into checksum
  sum += packet.acknum;
  sum += packet.seqnum;

  // return 1 if sums match 0 otherwise
  return !(packet.checksum == sum);
}

/* Funciton that checks if sequence number of packet matches expected sequence number */
bool correctSeqnumber(struct pkt packet)
{
  return !(packet.seqnum == seqnumber);
}

/* Function that sets next expected sequence number */
void nextSeqNumber()
{
  seqnumber = seqnumber ? 0 : 1;
}

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
  if (notcorrupt(packet) && correctSeqnumber(packet))
  {
    tolayer5('B', packet.payload);
    tolayer3('B', makepkt("ACK", seqnumber));
    nextSeqNumber();
  }

  // If not corrupt and incorrect sequencenumber
  else if (notcorrupt(packet) && !correctSeqnumber(packet))
  {
    tolayer3('B', makepkt("ACK", seqnumber));
  }

  // If corrupt
  else if (!notcorrupt(packet))
  {
    ;
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
