#ifndef DGA_HEADER_H
#define DGA_HEADER_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <netdb.h>
#include <stdbool.h>

#define TLD_SIZE 5
#define RAND_SIZE 150 // technically we only need 127 but this works...

// Possible TLDs
char* tlds [TLD_SIZE] = {".csc840.lan", ".com", ".press", ".me", ".cc"};

// Random array of letters and numbers
char rand_letters [RAND_SIZE] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

#endif