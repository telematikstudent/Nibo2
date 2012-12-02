/**
 ============================================================================
 @file       : fahren.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 0.1
 @brief		 : This source file contians funktion for driving and turning of the nibo
 ============================================================================
 */


#include "fahren.h"

/*
 * This function will drive forward by speed of 4 - 25 or backward by a speed of - 4 - (-25) and check
 * wether objects are in the way of the
 * nibo
 */
uint8_t drive(uint8_t speed){
	uint8_t out = drive_status_front_free;
	//aktuallisierung des coprozessors
	copro_update();
	copro_resetOdometry(0, 0);

	if(checkDriveDirection() == drive_status_front_free){
		copro_setSpeed(speed,speed);
	}else{
		copro_stop();
		out = drive_status_front_blocked;
	}
	delay(100);
	sendTicks();
	niboCom_putIRDistance(copro_distance);
	return out;
}

void turn_left(){
	copro_setTargetRel(-27, 27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_left);
	sendIRDistance();
}

void turn_halfLeft(){
	copro_setTargetRel(-13, 13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfLeft);
	sendIRDistance();
}

void turn_right(){
	copro_setTargetRel(27, -27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_right);
	sendIRDistance();
}

void turn_halfRight(){
	copro_setTargetRel(13, -13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfRight);
	sendIRDistance();
}

void turn_around(){
	copro_setTargetRel(53, -53, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_turn);
	sendIRDistance();
}



uint8_t checkDriveDirection(){

	//coprozessors update
	copro_update();

	if(copro_distance[1]/256 < irAbstand &&
	   copro_distance[2]/256 < irAbstand &&
	   copro_distance[3]/256 < irAbstand)
	{
		return drive_status_front_free;
	}
	else{
		//rechts && rechtsoben
		if (copro_distance[0] / 256 < irAbstand && copro_distance[1] / 256 < irAbstand){
			return drive_status_right_free;
		}
		//links && linksoben
		else if (copro_distance[4] / 256 < irAbstand && copro_distance[3] / 256 < irAbstand){
			return drive_status_left_free;
		}
		else{
			return drive_status_all_blocked;
		}
	}
}

void checkDistance(){
	copro_update();
	if((copro_distance[0]/256) > irAbstand){leds_set_status(LEDS_RED,7);}
	else{leds_set_status(LEDS_GREEN,7);}

	if((copro_distance[1]/256) > irAbstand){leds_set_status(LEDS_RED,6);}
	else{leds_set_status(LEDS_GREEN,6);}

	if((copro_distance[2]/256) > irAbstand){leds_set_status(LEDS_RED,5);leds_set_status(LEDS_RED,4);}
	else{leds_set_status(LEDS_GREEN,5);leds_set_status(LEDS_GREEN,4);}

	if((copro_distance[3]/256) > irAbstand){leds_set_status(LEDS_RED,3);}
	else{leds_set_status(LEDS_GREEN,3);}

	if((copro_distance[4]/256) > irAbstand){leds_set_status(LEDS_RED,2);}
	else{leds_set_status(LEDS_GREEN,2);}

}
void sendTicks(){
	copro_update();
	char output[13] = "";

	if(copro_ticks_l > 0){
		niboCom_putDistance(copro_ticks_l);
	}
	copro_resetOdometry(0, 0);
}

void sendIRDistance(){
	delay(2000);
	copro_resetOdometry(0, 0);
	copro_update();
	niboCom_putIRDistance(copro_distance);
}
