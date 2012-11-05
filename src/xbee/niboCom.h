/*
 * niboCom.h
 *
 *  Created on: 23.10.2012
 *      Author: defaultuser
 */

#ifndef NIBOCOM_H_
#define NIBOCOM_H_

/**
 * includes
 */

#include <nibo/niboconfig.h>
#include "uart0.h"
#include <stdbool.h>


/**
 * defines
 */

#define niboCom_default_baudrate 9600


void niboCom_init();

void niboCom_init_with_baud(uint16_t baudrate);

void niboCom_putchar(uint8_t c);

uint8_t niboCom_getchar();


#endif /* NIBOCOM_H_ */
