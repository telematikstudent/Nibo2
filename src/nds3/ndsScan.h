/**
 * @file		ndsScan.h
 * @author		Christian Witte
 * @date		Version 0.1
 * @brief		Headerfile: library for the NDS3 Module.
 */

#ifndef NDSSCAN_H_
#define NDSSCAN_H_

/**
 * includes
 */
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/copro.h>
#include <nibo/spi.h>
#include <nibo/nds3.h>
#include <nibo/i2cmaster.h>
#include <stdbool.h>


/**
 * @brief scans the surrounding of the nibo with the nds3
 * @param degree the angle resolution of the nds3 scan, defines the number of values returned -> (180/degree)+1
 * @return the nds measurement
 */
uint8_t *ndsScan(uint8_t degree);

/**
 * @brief initialize nds3 module
 */
void ndsScan_init();

#endif /* NDSSCAN_H_ */
