/**
 * @file		drive.c
 * @author		Phillip Kopprasch, Christian Witte
 * @date		Version 0.1
 * @brief		library for nibo movement.
 */

#include "drive.h"

/**
 * @brief moves the nibo forwards if no obstacle blocks the path
 * @param speed the speed the nibo moves in ticks
 * @return drive_front_free(1) or drive_direction_blocked(0) if the path is blocked
 */
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
	//transmit the moved distance and the ir sensor values
	delay(100);
	drive_sendTicks();
	drive_sendIRDistance(0);
	return out;
}

/**
 * @brief returns a non-blocked direction for the nibo
 * @return drive_front_free(1) or drive_right_free(2) or
 * drive_left_free(3) or drive_front_all_blocked(4).
 */
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

/**
 * @brief turns the nibo 90 degree to the left
 */
void drive_turn_left(){
	copro_setTargetRel(-27, 27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_left);
	drive_sendIRDistance(2000);
}

/**
 * @brief turns the nibo 45 degree to the left
 */
void drive_turn_halfLeft(){
	copro_setTargetRel(-13, 13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfLeft);
	drive_sendIRDistance(2000);
}

/**
 * @brief turns the nibo 90 degree to the right
 */
void drive_turn_right(){
	copro_setTargetRel(27, -27, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_right);
	drive_sendIRDistance(2000);
}

/**
 * @brief turns the nibo 45 degree to the right
 */
void drive_turn_halfRight(){
	copro_setTargetRel(13, -13, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_halfRight);
	drive_sendIRDistance(2000);
}

/**
 * @brief turns the nibo 180 degree to the right
 */
void drive_turn_around(){
	copro_setTargetRel(53, -53, 10);
	niboCom_putDircetionChange(niboCom_cmd_nibo_turn);
	drive_sendIRDistance(4000);
}

/**
 * @brief checks wheter the path in front of the nibo is blocked or not
 * @return drive_front_free(1) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isFrontFree(){
	if (copro_distance[1]/256 < IRDistance &&
		copro_distance[2]/256 < IRDistance &&
		copro_distance[3]/256 < IRDistance){
		return drive_front_free;
	}
	else return drive_direction_blocked;
}

/**
 * @brief checks wheter the path right of the nibo is blocked or not
 * @return drive_right_free(2) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isRightFree(){
	if (copro_distance[0] / 256 < IRDistance && copro_distance[1] / 256 < IRDistance){
				return drive_right_free;
	}
	else return drive_direction_blocked;
}

/**
 * @brief checks wheter the path left of the nibo is blocked or not
 * @return drive_left_free(3) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isLeftFree(){
	if (copro_distance[4] / 256 < IRDistance && copro_distance[3] / 256 < IRDistance){
		return drive_left_free;
	}
	else return drive_direction_blocked;
}

/**
 * @brief sends the moved distance of nibo via xbee
 */
void drive_sendTicks(){
	copro_update();

	if(copro_ticks_l > 0){
		niboCom_putDistance(copro_ticks_l);
	}
	copro_resetOdometry(0, 0);
}

/**
 * @brief sends the IR-sensor values  via xbee
 * @param ms delay before collection IR-sensor values
 */
void drive_sendIRDistance(int ms){
	delay(ms);
	copro_resetOdometry(0, 0);
	copro_update();
	niboCom_putIRDistance(copro_distance);
}

