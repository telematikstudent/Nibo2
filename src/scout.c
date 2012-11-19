/**
 *
 * param ndsMovement --> winkel der pro zyklus gefahren wird
 *
 * return Beispiel
 *
 * 000 <- alles frei
 * 101 <- nur geradezu frei
 */

#include "scout.h"

uint8_t checkDirectionsOnDistance(uint8_t ndsMovement, uint8_t ndsAufnahmeAbstand) {

	uint8_t richtung = 0;
	uint8_t winkel = 0;
	uint8_t distance = 0;

	bool left = false;
	bool mid = false;
	bool right = false;


	//einmal umschauen
	if (winkel <= 180 - ndsMovement) {
		// move NDS3 sensor, value in degrees
		nds3_move(winkel);
		winkel = winkel + ndsMovement;
	} else {
		if (left && !right && !mid) {
			 richtung = 1;
		} else if (!left && right && !mid) {
			 richtung = 100;
		} else if (!left && !right && mid) {
			 richtung = 10;
		} else if (left && right && !mid) {
			 richtung = 101;
		} else if (left && !right && mid) {
			 richtung = 011;
		} else if (!left && right && mid) {
			 richtung = 110;
		} else if (left && mid && right) {
			 richtung = 111;
		} else {
			 richtung = 0;
		}

		left = false;
		mid = false;
		right = false;
	}

	//aktuallisierung des coprozessors
	copro_update();
	distance = nds3_get_dist();

	if (winkel < 85 && distance < ndsAufnahmeAbstand) {
		left = true;
	}
	if (winkel < 95 && winkel > 85 && distance < ndsAufnahmeAbstand) {
		mid = true;
	}
	if (winkel < 180 && winkel > 95 && distance < ndsAufnahmeAbstand) {
		right = true;
	}

	return richtung;
}

/**
 * This fuctions returns the distance for the selected deegres
 */
uint8_t *checkObjektsOnDistance(uint8_t degrees) {

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

	niboStartScout(90);
	return points;
}

void niboStartScout(int winkel){

	nds3_move(winkel);
}
