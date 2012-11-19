/*
 * scout.h
 *
 *  Created on: 05.11.2012
 *      Author: Abjo
 */

#ifndef SCOUT_H_
#define SCOUT_H_

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
// Coprozessorfunktionen einbinden, da dieser die Motoren steuert
#include <nibo/copro.h>
// Kommunikationsfunktionen fuer die SPI Schnittstelle zum Coprozessor
#include <nibo/spi.h>
// NDS3 library
#include <nibo/nds3.h>
#include <stdbool.h>
// I2C interface function
#include <nibo/i2cmaster.h>


#include "zustaende.h"
#include "parameter.h"

uint8_t checkDirectionsOnDistance(uint8_t ndsMovement, uint8_t ndsAufnahmeAbstand);
uint8_t *checkObjektsOnDistance(uint8_t degrees);
void niboStartScout(int winkel);

#endif /* SCOUT_H_ */
