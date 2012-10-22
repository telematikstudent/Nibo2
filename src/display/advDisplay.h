/**
 ============================================================================
 @file       : advDisplay.h
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
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
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_init();

/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_clear();

/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_append_line(const char *txt);

/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_printVoltage();




#endif /* ADVDISPLAY_H_ */
