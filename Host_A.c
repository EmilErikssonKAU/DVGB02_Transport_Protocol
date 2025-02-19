#include "Sim_Engine.h"
#include <string.h>
#include "Host_A.h"



int acknum;
int seqnum;
  


int calculate_checksum(char payload[20]);

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message){


  float time  = 0;

  printf("hje  msg; %s\n", message.data);

  tolayer5(0, message.data);

  struct pkt packet; 

  packet.seqnum = acknum++;


  packet.acknum = seqnum++;
  
  packet.checksum = calculate_checksum(message.data);

  memcpy(packet.payload, message.data, sizeof(packet.payload));

  
  starttimer(0, time);



  printf("checksum  %d\n", packet.checksum);

  printf("seqnum  %d\n", packet.seqnum);

  printf("%s", packet.payload);
  
  tolayer3(0, packet); 

}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {

  

}

/* Called when A's timer goes off */
void A_timerinterrupt() {



  printf("hje A_timerinteruppt\n");
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




int calculate_checksum(char payload[20]){

  int sum = 0;

  for(int i = 0; i < 19; i++){

    sum = sum +payload[i];

  }

  return sum; 

}