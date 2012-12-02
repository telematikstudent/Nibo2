/**
 *
 * param ndsMovement --> winkel der pro zyklus gefahren wird
 *
 * return Beispiel
 *
 * 000 <- alles frei
 * 101 <- nur geradezu frei
 */

#include "ndsScan.h"


/**
 * This fuctions returns the distance for the selected deegres
 */
uint8_t *ndsScan(uint8_t degrees) {

	uint8_t winkel = 0;
	static uint8_t points[180] = {};

	for(winkel = 0; winkel < 180; winkel = winkel + degrees){

		nds3_move(winkel);

		//saving time for the movement of the servoengine, more for the first move
		if(winkel == 0){
			delay(500);
		}else {
			delay(100);
		}

		//updating the coprozessor, for the realtime value of the sensor
		copro_update();
		points[winkel / degrees] = nds3_get_dist();
	}

	ndsScan_init(90);
	return points;
}

void ndsScan_init(){
	i2c_init();
	nds3_move(90);
}
