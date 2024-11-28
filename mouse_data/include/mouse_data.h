#ifndef MOUSE_DATA_H
#define MOUSE_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief File pointer to the binary file to be wrtitten to and read.
 */
extern FILE *fptr;

/**
 * @brief Signal Handler used to receive the SIGINT signal and close the the
 * open binary file.
 *
 * User triggers SIGINT by inputing ctrl + C in the terminal.
 * @param sig Integer signal received.
 */
void handler(int sig);

#endif