#ifndef DDR_TEST_H
#define DDR_TEST_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned int memfill32( unsigned int dest, unsigned int len, unsigned int val );

int ddr_test();

#endif // DDR_TEST_H
