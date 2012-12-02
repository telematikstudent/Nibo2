/**
 ============================================================================
 @file       : fahren.c
 @author     : Phillip Kopprasch, Christian Witte
 @date	     : Version 0.1
 @brief		 : This source file contians funktion for driving and turning of the nibo
 ============================================================================
 */


#include "drive.h"


uint8_t drive(uint8_t speed){
	uint8_t out = drive_front_free;

	copro_update();
	copro_resetOdometry(0, 0);

	if(drive_isFrontFree()){
		copro_setSpeed(speed,speed);
	}else{
		copro_stop();
		out = drive_direction_blocked;
	}
	delay(100);
	drive_sendTicks();
	drive_sendIRDistance(0);
	return out;
}

void drive_turn_left(){
	copro_setTargetRel(-27, 27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_left);
	drive_sendIRDistance(2000);
}

void drive_turn_halfLeft(){
	copro_setTargetRel(-13, 13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfLeft);
	drive_sendIRDistance(2000);
}

void drive_turn_right(){
	copro_setTargetRel(27, -27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_right);
	drive_sendIRDistance(2000);
}

void drive_turn_halfRight(){
	copro_setTargetRel(13, -13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfRight);
	drive_sendIRDistance(2000);
}

void drive_turn_around(){
	copro_setTargetRel(53, -53, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_turn);
	drive_sendIRDistance(4000);
}



uint8_t drive_getFreePath(){

	copro_update();

	if(drive_isFrontFree()){
		return drive_front_free;
	}
	else if(drive_isRightFree()){
		return drive_right_free;
	}
	else if(drive_isLeftFree()){
		return drive_left_free;
	}
	else{
		return drive_all_blocked;
	}

}


uint8_t drive_isFrontFree(){
	if (copro_distance[1]/256 < irAbstand &&
		copro_distance[2]/256 < irAbstand &&
		copro_distance[3]/256 < irAbstand){
		return drive_front_free;
	}
	else return drive_direction_blocked;
}

uint8_t drive_isRightFree(){
	if (copro_distance[0] / 256 < irAbstand && copro_distance[1] / 256 < irAbstand){
				return drive_right_free;
	}
	else return drive_direction_blocked;
}

uint8_t drive_isLeftFree(){
	if (copro_distance[4] / 256 < irAbstand && copro_distance[3] / 256 < irAbstand){
		return drive_left_free;
	}
	else return drive_direction_blocked;
}

void drive_sendTicks(){
	copro_update();

	if(copro_ticks_l > 0){
		niboCom_putDistance(copro_ticks_l);
	}
	copro_resetOdometry(0, 0);
}

void drive_sendIRDistance(int ms){
	delay(ms);
	copro_resetOdometry(0, 0);
	copro_update();
	niboCom_putIRDistance(copro_distance);
}

