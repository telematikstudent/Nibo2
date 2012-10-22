/**
 ============================================================================
 @file       : advDisplay.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 1.0
 @brief		 : advanced library for the nibo display
 ============================================================================
 */




/**
 * includes
 */

#include "advDisplay.h"



void advDisplay_printVoltage(){
		char output[20] = "";
		double volt = 0;

		bot_update();
		volt = 0.0166 * bot_supply -1.19;
		sprintf(output, "VCC: %2.1f V", volt);

		gfx_move(logo_width,0);

		gfx_print_text(output);
}


/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_init(){
	display_init();
	gfx_init();

	gfx_move(0,0);
	gfx_draw_xbm_P(logo_width, logo_height, (PGM_P) logo_bits);
}


/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_clear(){


	int i = 0;
	cli();

	for(i = 10; i <= 50; i = i +10){
		gfx_move(logo_width, i);
		gfx_print_text("             ");
	}

	sei();

}

/**
 *	@brief
 *	@param
 *	@return
 */
void advDisplay_append_line(const char *txt){
	gfx_move(logo_width,10);
	gfx_print_text(txt);
}





