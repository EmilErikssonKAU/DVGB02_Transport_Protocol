#include "Sim_Engine.h"
#include "Host_A.h"
#include "Host_helpfunctions.h"
#include <string.h>
#include <stdbool.h>

// Macros
#define MAXQUESIZE 100
#define A 0

// Global variables
int seqnumA;
float Atime;
struct pkt sndpkt;
bool waiting_for_ack = false;
int front = 0, queue_size = 0;

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{

  if (!waiting_for_ack)
  {

    // waiting for ack state, (currently not mutex protected)
    waiting_for_ack = true;

    // set sequence number
    seqnumA = nextSeqNumber(seqnumA);
    sndpkt.seqnum = seqnumA;

    // set ack number (-1)
    sndpkt.acknum = -1;

    // set payload
    strcpy(sndpkt.payload, message.data);

    // set checksum
    sndpkt.checksum = getCheckSum(sndpkt);

    // printPacket(*pack);

    // start timer
    starttimer(A, Atime);

    // send packet to layer 3
    tolayer3(A, sndpkt);
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  //  Not corrupt and correct sequencenumber
  if (notcorrupt(packet) && correctAcknumber(packet, (seqnumA + 1) % 2))
  {
    //  stop timer
    stoptimer(A);

    // allow for next message in queue to be handled
    waiting_for_ack = false;
  }

  // Corrupt or incorrect sequencenumber
  else if (!notcorrupt(packet) || !correctAcknumber(packet, (seqnumA + 1) % 2))
  {
    //  resend packet
    tolayer3(A, sndpkt);

    // reset timer
    stoptimer(A);
    starttimer(A, Atime);
  }
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
  // resend packet
  tolayer3(0, sndpkt);

  // reset time
  starttimer(A, Atime);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
  seqnumA = 0;
  Atime = 50.0;
  sndpkt.acknum = 0;
  sndpkt.seqnum = 0;
  sndpkt.checksum = 0;
}
