#ifndef AS
#define AS

#include "Sim_Engine.h"
#include <stdbool.h>
void printPacket(struct pkt packet);

/* Function that calculates checksum of packet*/
int getCheckSum(struct pkt packet);

/* Function that checks if packet is corrupt */
bool notcorrupt(struct pkt packet);

/* Funciton that checks if sequence number of packet matches expected sequence number */
bool correctSeqnumber(struct pkt packet, int seqnumber);

/* Function that sets next expected sequence number */
int nextSeqNumber(int seqnumber);

bool correctAcknumber(struct pkt packet, int acknumber);

#endif