#include "Sim_Engine.h"
#include <string.h>



int acknum;
int seqnum;
  

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message){

  printf(" msg; %s\n", message.data);

  //tolayer5(0, message.data);

  struct pkt packet; 

  packet.seqnum = acknum;

  packet.acknum = seqnum;
  
  packet.checksum = 1;

  memcpy(packet.payload, message.data, sizeof(packet.payload));

  tolayer3(0, packet);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {



  printf("checksum  %d\n", packet.checksum);



}

/* Called when A's timer goes off */
void A_timerinterrupt() {



  printf("A_timerinteruppt\n");
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {

  printf("a initinilasing\n");


  acknum = 0;
  
  seqnum = 0;
  /* TODO */
}
