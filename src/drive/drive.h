/**
 * @file		drive.h
 * @author		Phillip Kopprasch, Christian Witte
 * @date		Version 0.1
 * @brief		Headerfile: library for nibo movement.
 */

#ifndef FAHREN_H_
#define FAHREN_H_


/**
 * includes
 */

/**
 * nibo
 */
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/copro.h>
#include <nibo/spi.h>
#include <nibo/delay.h>

/**
 * Martini
 */
#include "../xbee/niboCom.h"

/**
 * defines
 */

//path status
#define drive_direction_blocked		0

#define drive_front_free		1

#define drive_right_free		2

#define drive_left_free		3

#define drive_all_blocked	4

//obstacle recognized threshold
#define IRDistance  70

/**
 * @brief moves the nibo forwards if no obstacle blocks the path
 * @param speed the speed the nibo moves in ticks
 * @return drive_front_free(1) or drive_direction_blocked(0) if the path is blocked
 */
uint8_t drive(uint8_t speed);

/**
 * @brief returns a non-blocked direction for the nibo
 * @return drive_front_free(1) or drive_right_free(2) or
 * drive_left_free(3) or drive_front_all_blocked(4).
 */
uint8_t drive_getFreePath();

/**
 * @brief turns the nibo 90 degree to the left
 */
void drive_turn_left();

/**
 * @brief turns the nibo 45 degree to the left
 */
void drive_turn_halfLeft();

/**
 * @brief turns the nibo 90 degree to the right
 */
void drive_turn_right();

/**
 * @brief turns the nibo 45 degree to the right
 */
void drive_turn_halfRight();

/**
 * @brief turns the nibo 180 degree to the right
 */
void drive_turn_around();

/**
 * @brief checks wheter the path in front of the nibo is blocked or not
 * @return drive_front_free(1) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isFrontFree();

/**
 * @brief checks wheter the path right of the nibo is blocked or not
 * @return drive_right_free(2) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isRightFree();

/**
 * @brief checks wheter the path left of the nibo is blocked or not
 * @return drive_left_free(3) or drive_direction_blocked(0) if path is blocked
 */
uint8_t drive_isLeftFree();

/**
 * @brief sends the moved distance of nibo via xbee
 */
void drive_sendTicks();

/**
 * @brief sends the IR-sensor values  via xbee
 * @param ms delay before collection IR-sensor values
 */
void drive_sendIRDistance(int delay);

#endif /* FAHREN_H_ */
