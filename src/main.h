/**
 * @file		main.c
 * @author		Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 * @date		Version 0.1
 * @brief		Headerfile: Main program for nibo, including the main loop.
 */


#ifndef MAIN_H_
#define MAIN_H_

/**
 * includes
 */

/**
 * stdlib
 */
#include <stdbool.h>

/**
 * nibo
 */
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/delay.h>
#include <nibo/leds.h>
#include <nibo/sound.h>
#include "sound/n2sound.h"

/**
 * AVR
 */
#include <avr/interrupt.h>

/**
 * Martini
 */
#include "xbee/niboCom.h"
#include "drive/drive.h"
#include "display/advDisplay.h"
#include "nds3/ndsScan.h"


/**
 * defines
 */

#define MODE_MAN		0

#define MODE_AUTO		1

#define NDS_SCAN_DEG	2

/**
 * @brief moves the nibo around automagically
 */
void autoMode();

/**
 * @brief checks the values of the IR-sensors and switches the leds depending on the value.
 */
void checkDistance();

#endif /* MAIN_H_ */
