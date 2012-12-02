/*
 * fahren.h
 *
 *  Created on: 26.11.2012
 *      Author: Abjo
 */

#ifndef FAHREN_H_
#define FAHREN_H_

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
// Coprozessorfunktionen einbinden, da dieser die Motoren steuert
#include <nibo/copro.h>
// Kommunikationsfunktionen fuer die SPI Schnittstelle zum Coprozessor
#include <nibo/spi.h>
// Interrupts fuer die Kommunikation mit dem Coprozessor
#include <avr/interrupt.h>
#include <stdbool.h>
#include <nibo/leds.h>
#include <nibo/delay.h>

#include "../xbee/niboCom.h"

#define drive_direction_blocked		0

#define drive_front_free		1

#define drive_right_free		3

#define drive_left_free		4

#define drive_all_blocked	5


#define irAbstand  70

uint8_t drive(uint8_t speed);
uint8_t drive_getFreePath();

void drive_turn_right();
void drive_turn_left();
void drive_turn_halfRight();
void drive_turn_halfLeft();
void drive_turn_around();

uint8_t drive_isFrontFree();
uint8_t drive_isRightFree();
uint8_t drive_isLeftFree();

void drive_sendTicks();
void drive_sendIRDistance(int delay);

#endif /* FAHREN_H_ */
