#include "Sim_Engine.h"
#include <stdbool.h>
#include <string.h>

/* Prints packet contents*/
void printPacket(struct pkt packet)
{
    printf("SEQNUM: %d\n ACKNUM: %d\n CHECKSUM %d\n PAYLOAD: %s\n", packet.seqnum, packet.acknum, packet.checksum, packet.payload);
}

/* Function that calculates checksum of packet*/
int getCheckSum(struct pkt packet)
{
    int sum = 0;

    // Calculate checksum of payload
    for (int i = 0; i < strlen(packet.payload); i++)
    {
        sum += packet.payload[i];
    }

    // Inlcude acknum and seqnum into checksum
    sum += packet.acknum;
    sum += packet.seqnum;

    return sum;
}

/* Function that checks if packet is corrupt */
bool notcorrupt(struct pkt packet)
{
    // return 1 if sums match 0 otherwise
    return (packet.checksum == getCheckSum(packet));
}

/* Funciton that checks if sequence number of packet matches expected sequence number */
bool correctSeqnumber(struct pkt packet, int seqnumber)
{
    return !(packet.seqnum == seqnumber);
}

/* Function that sets next expected sequence number */
int nextSeqNumber(int seqnumber)
{
    seqnumber = seqnumber ? 0 : 1;
    return seqnumber;
}