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


/**
 * comands
 */
#define niboCom_cmd_reserved 		0
#define niboCom_cmd_ir_distance 	1
#define niboCom_cmd_nds_distance 	2
#define niboCom_cmd_nibo_distance	3

//mode
#define niboCom_cmd_nibo_auto		10
#define niboCom_cmd_nibo_man		11

#define niboCom_cmd_nibo_drive		12
//directions
#define niboCom_cmd_nibo_halfLeft	13
#define niboCom_cmd_nibo_left		14
#define niboCom_cmd_nibo_halfRight	15
#define niboCom_cmd_nibo_right		16
#define niboCom_cmd_nibo_turn		17



void niboCom_init();


void niboCom_init_with_baud(uint16_t baudrate);

void niboCom_putPackage(uint8_t cmd, uint8_t size, uint8_t *data);

void niboCom_putIRDistance(uint16_t *data);

void niboCom_putNDSDistance(int size, uint8_t *data);


void niboCom_putdircetionChange(uint8_t direction);


void niboCom_putDistance(uint8_t ticks);


uint8_t niboCom_getCMD();

void niboCom_setAuto(bool mode);



#endif /* NIBOCOM_H_ */
