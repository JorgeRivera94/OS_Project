#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mouse_data.h"

int main() {
  // Structure to recieve and handle SIGINT signal when user enters ctrl + C in
  // terminal
  struct sigaction sa;
  sa.sa_handler = handler;
  sigaction(SIGINT, &sa, NULL);

  const char *device = "/dev/input/mice"; // Generic mouse device file
  int fd = open(device, O_RDONLY);
  if (fd == -1) {
    perror("Error opening device");
    return 1;
  }

  signed char data[3];

  printf("Listening for mouse events. Move the mouse or press buttons.\n");

  // Variables to store the sumation of x and y deltas (absolute mouse
  // coordinates)
  int sx = 0;
  int sy = 0;

  // Variables to store the virtual coordinates of the mouse
  float vx;
  float vy;

  // Open the binary file
  fptr = fopen("mouse_data.dat", "wb");

  while (1) {
    if (read(fd, data, sizeof(data)) > 0) {
      int left = data[0] & 0x1;
      int right = data[0] & 0x2;
      int middle = data[0] & 0x4;
      int dx = data[1];
      int dy = data[2];

      // Capture the absolute x coordinate by storing the sumation of all dx
      sx += dx;

      // Capture the absolute y coordinate by storing the sumation of all dy
      sy += dy;

      // Transform the absolute x coordinates to a [0,100] range
      vx = (100.0 / 1023.0) * (sx + 512.0);

      // Transform the absolute y coordinates to a [0,25] range
      vy = (25.0 / 767.0) * (sy + 383.0);

      // Write into the binary file
      int x = (int)vx;
      int y = (int)vy;
      fwrite(&x, sizeof(int), 1, fptr);
      fwrite(&y, sizeof(int), 1, fptr);
    }
  }

  close(fd);
  return 0;
}