/**
 ============================================================================
 @file       : Application.c
 @author     : Phillip Kopprasch
 @date	     : Version 1.0
 @brief		 : Main .c-File for Martini-Nibo-Projekt
 ============================================================================
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_


/**
 * defines
 */
#define timer_limit 256
#define ir_sensor_limit 70

/**
 * includes std
 */
#include <stdbool.h>

/**
 * includes avr
 */

/**
 * includes nibo
 */
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/floor.h>
#include <nibo/copro.h>
#include <nibo/spi.h>
#include <avr/interrupt.h>
#include <nibo/sound.h>
#include <nibo/delay.h>
#include <nibo/leds.h>
#include <nibo/uart0.h>
#include <nibo/i2cmaster.h>




/**
 * includes Martini
 */

#include "display/advDisplay.h"

void checkDistance();

void initNibo();

int main(void);


#endif /* APPLICATION_H_ */
