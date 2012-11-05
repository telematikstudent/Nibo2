/**
 ============================================================================
 @file       : niboCom.c
 @author     : Phillip Kopprasch
 @date	     : Version 1.0
 @brief		 : library for nibo2pc communication
 ============================================================================
 */

/**
 * includes
 */

#include "niboCom.h"

bool niboCom_auto = false;

void niboCom_init(){
	niboCom_init_with_baud(niboCom_default_baudrate);
}


void niboCom_init_with_baud(uint16_t baudrate){
		uart0_set_baudrate(baudrate);
		uart0_enable();
}


void niboCom_putchar(uint8_t c){
	while(uart0_txfull() == true);
	uart0_putchar(c);
}

uint8_t niboCom_getchar(){
	if(uart0_rxempty()==false) return uart0_getchar();
	return 0;
}


void niboCom_putPackage(uint8_t cmd, uint8_t size, uint8_t *data){
	int i = 0;

	niboCom_putchar(0x68);
	niboCom_putchar(cmd);
	niboCom_putchar(size);
	for(i = 0; i < size;i++){
		niboCom_putchar(data[i]);
	}
	niboCom_putchar(0x16);
}

void niboCom_putIRDistance(uint16_t *data){
	int i = 0;
	uint8_t distance[5];
	for(i = 0; i < 5;i++){
		distance[i] = data[i]/256;
	}

	niboCom_putPackage(niboCom_cmd_ir_distance,5, distance);
}

void niboCom_putNDSDistance(int size, uint8_t *data){
	int i = 0;
	uint8_t distance[size];
	for(i = 0; i < size;i++){
		distance[i] = data[i]/256;
	}

	niboCom_putPackage(niboCom_cmd_nds_distance,size, distance);
}


void niboCom_putdircetionChange(uint8_t direction){
	niboCom_putPackage(direction,0,0);
}


void niboCom_putDistance(uint8_t ticks){
	niboCom_putPackage(niboCom_cmd_nibo_distance,1,ticks);
}


uint8_t niboCom_getCMD(){
	if(niboCom_auto == true) return niboCom_cmd_nibo_auto;
	else return niboCom_cmd_nibo_man;
}

void niboCom_setAuto(bool mode){
	niboCom_auto = mode;
}
