/*
 * Main.h
 *
 *  Created on: 26.11.2012
 *      Author: Abjo
 */

#ifndef MAIN_H_
#define MAIN_H_

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "xbee/niboCom.h"
#include "drive/drive.h"
#include "display/advDisplay.h"
#include "nibo/i2cmaster.h"
#include "nds3/ndsScan.h"
#include <nibo/sound.h>
#include "sound/n2sound.h"

#define MODE_AUTO		1

#define MODE_MAN		0

#define NDS_SCAN_DEG	2


void initBot();
void reset(uint8_t LastStatus,uint8_t status);




#endif /* MAIN_H_ */
