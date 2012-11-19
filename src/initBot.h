/*
 * initBot.h
 *
 *  Created on: 05.11.2012
 *      Author: Abjo
 */

#ifndef INITBOT_H_
#define INITBOT_H_


// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <avr/interrupt.h>
#include "zustaende.h"
#include <nibo/leds.h>


void initBot();
uint8_t reset(uint8_t LastStatus,uint8_t status);

#endif /* INITBOT_H_ */
