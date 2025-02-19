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

int front = 0, rear = -1, queue_size = 0;

struct msg sendque[MAXQUESIZE];

/* Shift queue one step to the left*/
void shiftqueue()
{
  // shift every element ot the left
  for (int i = 0; i < queue_size - 1; i++)
  {
    sendque[i] = sendque[i + 1];
  }
  // Clear last element
  memset(&sendque[queue_size - 1], 0, sizeof(struct msg));
}

/* Enqueue a message */
void enqueue(struct msg message)
{
  if (queue_size < MAXQUESIZE)
  {
    // increment
    queue_size++;

    // place message at the back
    sendque[queue_size] = message;
  }
  else
  {
    // Alert user of dropped packet
    printf("Queue is full! Dropping packet.\n");
  }
}

/* Dequeue a message */
struct msg dequeue()
{
  // dequeue first message
  struct msg message = sendque[0];
  queue_size--;

  // shift queue to prevent gaps
  shiftqueue(sendque);
  return message;
}

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
  // Place message in queue if waiting for ACK
  if (waiting_for_ack)
  {
    enqueue(message);
  }
  else
  {
    // waiting for ack state, (currently not mutex protected)
    waiting_for_ack = true;

    // set sequence number
    sndpkt.seqnum = nextSeqNumber(seqnumA);

    // set ack number (-1)
    sndpkt.acknum = -1;

    // copy payload
    memcpy(sndpkt.payload, message.data, sizeof(sndpkt.payload));

    // set checksum
    sndpkt.checksum = getCheckSum(sndpkt);

    // send packet to layer 3
    tolayer3(A, sndpkt);

    // start timer
    Atime = 0;
    starttimer(A, Atime);
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  // Not corrupt and correct sequencenumber
  if (notcorrupt(packet) && correctSeqnumber(packet, seqnumA))
  {
    // allow for next message in queue to be handled
    waiting_for_ack = false;

    // stop timer
    stoptimer(A);
  }

  // Corrupt or incorrect sequencenumber
  else if (notcorrupt(packet) && !correctSeqnumber(packet, seqnumA))
  {
    // resend packet
    tolayer3(A, sndpkt);

    // reset timer
    Atime = 0;
    starttimer(A, Atime);
  }
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
  // resend packet
  tolayer3(0, sndpkt);

  // reset time
  Atime = 0;
  starttimer(0, Atime);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
  seqnumA = 0;
  Atime = 0;
}
