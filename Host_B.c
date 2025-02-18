#include "Sim_Engine.h"


/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {


  printf("hje b msg  %s\n ", packet.payload);
 // printf("hej b checksum %d\n", packet.checksum);


  ///tolayer3(1, packet);


  /* TODO */
}

/* Called when B's timer goes off */
void B_timerinterrupt() {


  printf("B_timerinterupt\n");


  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {



  printf("b_init");





  /* TODO */
}
