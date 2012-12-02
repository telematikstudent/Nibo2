/**
 * @file		ndsScan.c
 * @author		Christian Witte
 * @date		Version 0.1
 * @brief		Headerfile: library for the NDS3 Module.
 */

#include "ndsScan.h"


/**
 * @brief scans the surrounding of the nibo with the nds3
 * @param degree the angle resolution of the nds3 scan, defines the number of values returned -> (180/degree)+1
 * @return the nds measurement
 */
uint8_t *ndsScan(uint8_t degree) {

	uint8_t winkel = 0;
	static uint8_t points[180] = {};

	for(winkel = 0; winkel < 180; winkel = winkel + degree){

		nds3_move(winkel);

		//delay for the movement of the servo, more for the first move
		if(winkel == 0){
			delay(900);
		}else {
			delay(100);
		}

		//updating the coprozessor, to get the current value
		copro_update();
		points[winkel / degree] = nds3_get_dist();
	}

	nds3_move(90);
	return points;
}

/**
 * @brief initialize nds3 module
 */
void ndsScan_init(){
	i2c_init();
	nds3_move(90);
}
