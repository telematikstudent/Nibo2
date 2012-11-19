/**
 ============================================================================
 @file       : fahren.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 0.1
 @brief		 : This source file contians funktion for driving and turning of the nibo
 ============================================================================
 */


#include "fahren.h"
#include "parameter.h"
/*
 * This function will drive forward by speed of 4 - 25 or backward by a speed of - 4 - (-25) and check
 * wether objects are in the way of the
 * nibo
 */
uint8_t drive(uint8_t speed){
	//aktuallisierung des coprozessors
	copro_update();

	if(copro_distance[0]/256 < irAbstand && copro_distance[1]/256 < irAbstand &&
	   copro_distance[2]/256 < irAbstand && copro_distance[3]/256 < irAbstand && copro_distance[4]/256 < 100 ){
		copro_setSpeed(speed,speed);
	}else{
		copro_stop();
		return rueckWende;
	}

	return fahren;
}
/**
 * 1 hinten-rechts
 * 2 hinten-links
 * 3 stelle rechts
 * 4 stelle links
 */
uint8_t wenden(uint8_t richtung) {
	static bool backdone = false;

	//aktuallisierung des coprozessors
	copro_update();

	switch (richtung) {
	case 1:
		if (copro_ticks_l > wendeweg && copro_ticks_l > wendeweg / 2) {
			copro_setSpeed(-20, -12);
		} else {
			return fahren;
		}
		;
		break;

	case 2:
		if (copro_ticks_l > wendeweg / 2 && copro_ticks_l > wendeweg) {
			copro_setSpeed(-12, -20);
		} else {
			return fahren;
		}
		break;
	case 3:

		if(copro_ticks_l > -50 && !backdone){
			copro_setSpeed(-20,-20);
		}
		else{

			if(!backdone){
				copro_stop();
				copro_resetOdometry(0, 0);
				backdone = true;
			}

			if (copro_ticks_l < 35 && copro_ticks_r < 75) {
				copro_setSpeed(12, -12);
			} else {
				copro_stop();
				return 1;
			}

		}

		break;
	}

	return rueckWende;
}

uint8_t checkDriveDirection(){

	//coprozessors update
	copro_update();

	if(copro_distance[0]/256 < irAbstand && copro_distance[1]/256 < irAbstand &&
	   copro_distance[2]/256 < irAbstand && copro_distance[3]/256 < irAbstand && copro_distance[4]/256 < 100 )
	{
		return 3;
	}
	else{
		//rechts && rechtsoben
		if (copro_distance[0] / 256 < irAbstand && copro_distance[1] / 256 < irAbstand){
			return 1;
		}
		//links && linksoben
		else if (copro_distance[4] / 256 < irAbstand && copro_distance[3] / 256 < irAbstand){
			return 2;
		}
		else{
			return 0;
		}
	}
}
