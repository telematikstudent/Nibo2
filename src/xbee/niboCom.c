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




void niboCom_init(){
	niboCom_init_with_baud(niboCom_default_baudrate);
}


void niboCom_init_with_baud(uint16_t baudrate){

		uart0_set_baudrate(baudrate);
		uart0_enable();
}


void niboCom_putchar(uint8_t c){
	if(uart0_txfull()==false) uart0_putchar(c);
}

uint8_t niboCom_getchar(){
	if(uart0_rxempty()==false) return uart0_getchar();
	return 0;
}
