/**
 ============================================================================
 @file       : advDisplay.c
 @author     : Marcus Tenbusch
 @date	     : Version 1.0
 @brief		 : advanced library for the nibo display
 ============================================================================
 */

/**
 * includes
 */

#include "advDisplay.h"

/**
 * vars
 */

/**
 * array of strings holds the lines appended to the terminal
 */
char terminal_text[terminal_lines][20] = {"", "", "", "", ""};

/**
 * index of the first line in terminal_text
 */
int terminal_head = 0;

/**
 * number of lines in the terminal
 * only increases until maximum never decreases
 */
int terminal_count = 0;


/**
 * @brief prints the current Voltage on the display
 */
void advDisplay_printVoltage(){
		char output[20] = "";
		double volt = 0;

		//get currente voltage value
		bot_update();
		//calculate the voltage from adc-value
		volt = 0.0166 * bot_supply -1.19;
		//concat output string
		sprintf(output, "VCC: %2.1f V", volt);

		//move to the position on the display where to write
		gfx_move(logo_width,0);

		//draw text
		gfx_print_text(output);
}


/**
 *	@brief initializes the advanced Display library
 */
void advDisplay_init(){
	//init diplay an graphics lib
	display_init();
	gfx_init();

	//move to top left corner and draw logo
	gfx_move(0,0);
	gfx_draw_xbm_P(logo_width, logo_height, (PGM_P) logo_bits);
}


/**
 *	@brief clears the terminal area of the display
 */
void advDisplay_clear(){

	int i = 0;
	//stop interrupts
	cli();

	//clear with whitespaces
	for(i = 10; i <= 50; i = i +10){
		gfx_move(logo_width, i);
		gfx_print_text("             ");
	}

	for(i = 0; i < terminal_lines; i++){
		strcpy(terminal_text[i],"                    ");
	}

	terminal_head = 0;
	terminal_count = 0;

	//enable interrupts
	sei();
}

/**
 *	@brief appends a line to the advDisplay terminal -> display can show the last #terminal_lines lines
 *	@param string to append
 */
void advDisplay_append_line(char *txt){

	//calculate index for the new line in terminal_text
	int index = (terminal_head + terminal_count)%terminal_lines;

	//copy the line into terminal_text array at calculated index
	strcpy(terminal_text[index], txt);

	if(terminal_count < 5){
		terminal_count++;
	}
	else{
		terminal_head = (terminal_head++)%terminal_lines;
	}

	//refresh the terminal output on the display
	advDisplay_printTerminal();
}

/**
 * prints all lines in terminal_text to the display
 */
void advDisplay_printTerminal(){
	int i;
	int index;

	for(i = 0; i < terminal_count;i++){

		//clear line
		gfx_move(logo_width,10 + 10*i);
		gfx_print_text("                      ");

		//print line
		index = (terminal_head + i)%terminal_lines;
		gfx_move(logo_width,10 + 10*i);
		gfx_print_text(terminal_text[index]);
		delay(10);
	}

}









