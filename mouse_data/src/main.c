#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  const char *device = "/dev/input/mice"; // Generic mouse device file
  int fd = open(device, O_RDONLY);
  if (fd == -1) {
    perror("Error opening device");
    return 1;
  }

  signed char data[3];

  printf("Listening for mouse events. Move the mouse or press buttons.\n");

  int sx = 0;
  int sy = 0;
  double vx;
  double vy;

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

      printf("sx: %d, sy: %d, vx: %f, vy: %f\n", sx, sy, vx, vy);
    }
  }

  close(fd);
  return 0;
}