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
#include <avr/interrupt.h>


/**
 * defines
 */

#define niboCom_default_baudrate 9600


/**
 * comands
 */
#define niboCom_cmd_none	 		0

//mode
#define niboCom_cmd_nibo_auto		1
#define niboCom_cmd_nibo_man		2

#define niboCom_cmd_ir_distance 	3
#define niboCom_cmd_nds_distance 	4
#define niboCom_cmd_nibo_distance	5
#define niboCom_cmd_nibo_drive		6
//directions
#define niboCom_cmd_nibo_turn		10
#define niboCom_cmd_nibo_halfLeft	11
#define niboCom_cmd_nibo_left		12
#define niboCom_cmd_nibo_halfRight	13
#define niboCom_cmd_nibo_right		14



void niboCom_uartInterrupt();

void niboCom_init();

void niboCom_init_with_baud(uint16_t baudrate);

void niboCom_putPackage(uint8_t cmd, uint8_t size, uint8_t *data);

void niboCom_putIRDistance(uint16_t *data);

void niboCom_putNDSDistance(int size, uint8_t *data);

void niboCom_putDircetionChange(uint8_t direction);

void niboCom_putDistance(uint8_t ticks);

uint8_t niboCom_getCMD();

void niboCom_setAuto(bool mode);



#endif /* NIBOCOM_H_ */
