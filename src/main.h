/*
 * cMain.h
 *
 *  Created on: 26.11.2012
 *      Author: Abjo
 */

#ifndef CMAIN_H_
#define CMAIN_H_

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "xbee/niboCom.h"
#include "antrieb/fahren.h"
#include "display/advDisplay.h"
#include "nibo/i2cmaster.h"
#include "nds3/scout.h"
#include <nibo/sound.h>
#include "n2sound.h"

#define warten			0

#define drive_status_front_free			1

#define drive_status_front_blocked 		2

#define scout 			3

#define defaultstatus 	0

#define MODE_AUTO		1

#define MODE_MAN		0

#define NDS_SCAN_DEG	2


void initBot();
void reset(uint8_t LastStatus,uint8_t status);




#endif /* CMAIN_H_ */
