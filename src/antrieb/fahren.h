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

#include "../xbee/niboCom.h"

#define warten		0

#define drive_status_front_free		1

#define drive_status_front_blocked 	2

#define drive_status_right_free		3

#define drive_status_left_free		4

#define drive_status_all_blocked	5


#define scout 	3

#define irAbstand  70

#define wendeweg  70

uint8_t drive(uint8_t speed);
uint8_t wenden(uint8_t richtung);
uint8_t checkDriveDirection();

void turn_right();
void turn_left();
void turn_halfRight();
void turn_halfLeft();
void turn_around();

void checkDistance();
void sendTicks();


#endif /* FAHREN_H_ */
