#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "bldc.h"

int main(int argc, char **argv)
{

  const char *bldc_id_str = argv[1];
  int bldc_id;
  const char *can_interf = "can0";

  int can_socket;
  struct ifreq can_ifr;
  struct sockaddr_can can_addr;
  struct can_frame frame1;

  int32_t erpm;
  int nbytes;

  if (argc <= 1 || argc >= 3)
  {
    printf("Error: Improper number of arguments\n");
    printf("Use: speedtest can-id\n");
    printf("     can-id = bldc id (number)\n");
    return 0;
  }
  bldc_id = atoi(bldc_id_str);

  // Setup CAN interface:
  can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  strcpy(can_ifr.ifr_name, can_interf);
  if (ioctl(can_socket, SIOCGIFINDEX, &can_ifr) < 0)
  {
    printf("ERROR unable to connect to interface: %s\n", can_ifr.ifr_name);
    return -1;
  }
  printf("Connected to socket: %s\n", can_ifr.ifr_name);
  can_addr.can_family = AF_CAN;
  can_addr.can_ifindex = can_ifr.ifr_ifindex;

  if (bind(can_socket, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0)
  {
    perror("Error in socket bind");
    return -2;
  }
  printf("Set speed 1000\n");
  bldc_set_erpm(&frame1, bldc_id, 1000);
  for (int i = 0; i < 50; i++)
  {
    nbytes = write(can_socket, &frame1, sizeof(struct can_frame));  // could check nbytes and retry 
    usleep(100000); // 100 msec
  }
  printf("Set speed 2000\n");
  bldc_set_erpm(&frame1, bldc_id, 2000);
  for (int i = 0; i < 50; i++)
  {
    nbytes = write(can_socket, &frame1, sizeof(struct can_frame));   // could check nbytes and retry 
    usleep(100000); // 100 msec
  }
  // It will stop anyway beacuse of the safety watchdog of about 2 seconds
  bldc_set_erpm(&frame1, bldc_id, 0);
  nbytes = write(can_socket, &frame1, sizeof(struct can_frame));   // could check nbytes and retry 
}
