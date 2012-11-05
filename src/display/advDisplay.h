/**
 ============================================================================
 @file       : advDisplay.h
 @author     : Marcus Tenbusch
 @date	     : Version 1.0
 @brief		 : advanced library for the nibo display
 ============================================================================
 */

#ifndef ADVDISPLAY_H_
#define ADVDISPLAY_H_

/**
 * defines
 */
#define display_height 64
#define display_width 128
#define line_Height 10
#define terminal_lines 5


/**
 * includes nibo
 */
#include <nibo/niboconfig.h>
#include <nibo/display.h>
#include <nibo/gfx.h>
#include <nibo/bot.h>

/**
 *includes avr
 */
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

/**
 * includes other
 */
#include "logo.xbm"
#include <stdio.h>


/**
 *	@brief initializes the advanced Display library
 */
void advDisplay_init();

/**
 *	@brief clears the terminal area of the display
 */
void advDisplay_clear();

/**
 *	@brief appends a line to the advDisplay terminal -> display can show the last #terminal_lines lines
 *	@param string to append
 */
void advDisplay_append_line(const char *txt);

/**
 * @brief prints the current Voltage on the display
 */
void advDisplay_printVoltage();




#endif /* ADVDISPLAY_H_ */
