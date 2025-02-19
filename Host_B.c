#include "Sim_Engine.h"



int calculate_checksumB(char payload[20]);

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {

  if (packet.checksum == calculate_checksumB( packet.payload)){
    printf("bra    ");
  }
  else{
    printf("dåligt ");
  }

  printf("checksum %d calculted chechsum %d \n\n\n", packet.checksum, calculate_checksumB( packet.payload));



  printf("hje b msg %s\n ", packet.payload);
 // printf("hje b seq %d\n", packet.seqnum);
  //printf("hje b ack %d\n", packet.acknum);
 // printf("hej b che %d\n", packet.checksum);
 // printf("hej b checksum %d\n", packet.checksum);


  ///tolayer3(1, packet);

  struct pkt {
    int seqnum;
    int acknum;
    int checksum;
    char payload[20];
 };
 
  /* TODO */
}

/* Called when B's timer goes off */
void B_timerinterrupt() {


  printf("hje B_timerinterupt\n");


  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {



  printf("b_init\n");


  /* TODO */
}


int calculate_checksumB(char payload[20]){

  int sum = 0;

  for(int i = 0; i < 19; i++){
    sum = sum +payload[i];
  }

  return sum; 

}