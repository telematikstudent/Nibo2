/*
 * showParameter.h
 *
 *  Created on: 05.11.2012
 *      Author: Abjo
 */

#ifndef SHOWPARAMETER_H_
#define SHOWPARAMETER_H_

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/copro.h>
//Biblio fürs Display
#include <stdio.h>
#include <nibo/delay.h>
#include <nibo/display.h>
#include <nibo/gfx.h>

void showParameter(uint8_t status, uint8_t richtung, uint8_t winkel, uint8_t distance);

#endif /* SHOWPARAMETER_H_ */
