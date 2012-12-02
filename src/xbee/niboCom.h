/**
 * @file		niboCom.h
 * @author		Phillip Kopprasch
 * @date		Version 0.1
 * @brief		Headerfile: library for nibo2pc communication.
 */

#ifndef NIBOCOM_H_
#define NIBOCOM_H_

/**
 * includes
 */
#include <stdbool.h>
#include <avr/interrupt.h>
#include <nibo/niboconfig.h>
#include "uart0.h"

/**
 * defines
 */

#define niboCom_default_baudrate 9600
#define niboCom_bufferSize 10

/**
 * niboCom comands
 */
#define niboCom_cmd_none	 		0

//mode
#define niboCom_cmd_nibo_auto		1
#define niboCom_cmd_nibo_man		2

#define niboCom_cmd_ir_distance 	3
#define niboCom_cmd_nds_distance 	4
#define niboCom_cmd_nibo_distance	5
#define niboCom_cmd_nibo_drive		6
#define niboCom_cmd_nibo_stop		7
//directions
#define niboCom_cmd_nibo_turn		10
#define niboCom_cmd_nibo_halfLeft	11
#define niboCom_cmd_nibo_left		12
#define niboCom_cmd_nibo_halfRight	13
#define niboCom_cmd_nibo_right		14

/**
 *@brief initializes xbee communication
 */
void niboCom_init();

/**
 * @brief sends a IRDistance packet via xbee
 * @param data the values of the ir sensors
 */
void niboCom_putIRDistance(uint16_t *data);

/**
 * @brief sends a NDSDistance packet via xbee
 * @param size the number of nds values
 * @param data the nds measurement values
 */
void niboCom_putNDSDistance(uint8_t size, uint8_t *data);

/**
 * @brief sends a DirectionChange packet via xbee
 * @param direction the direction change the nibo made
 */
void niboCom_putDircetionChange(uint8_t direction);

/**
 * @brief sends a Distance packet via xbee
 * @param ticks the number of ticks the nibo moved
 */
void niboCom_putDistance(uint8_t ticks);

/**
 * @brief tries to catch a command send via xbee
 * @return the last command received via xbee or
 * niboCom_cmd_none(0) if no new command was received
 */
uint8_t niboCom_getCMD();

/**
 * @brief is called on the USART0_RX_vect interrupt,
 * receives char send via xbee and tries to recognize niboCom packets
 */
void niboCom_uartInterrupt();


#endif /* NIBOCOM_H_ */
