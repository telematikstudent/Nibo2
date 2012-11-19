/*
 * wenden.h
 *
 *  Created on: 05.11.2012
 *      Author: defaultuser
 */

#ifndef WENDEN_H_
#define WENDEN_H_

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

#include "zustaende.h"
#include "parameter.h"



uint8_t drive(uint8_t speed);
uint8_t wenden(uint8_t richtung);
uint8_t checkDriveDirection();

#endif /* WENDEN_H_ */
