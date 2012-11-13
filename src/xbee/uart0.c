/*  BSD-License:

Copyright (c) 2007 by Nils Springob, nicai-systems, Germany

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  * Neither the name nicai-systems nor the names of its contributors may be
    used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "nibo/niboconfig.h"
#ifndef NIBO_USE_UART0
#error NIBO_USE_UART0 must be defined in niboconfig.h when this file is compiled
#endif

#include <avr/interrupt.h>

#include "nibo/uart0.h"
#include "niboCom.h"

#ifdef __cplusplus
extern "C" {
#endif



uint8_t uart0_txbuf[UART0_TXBUF_SIZE];
uint8_t uart0_rxbuf[UART0_RXBUF_SIZE];

uint8_t uart0_txbuf_begin;
uint8_t uart0_txbuf_end;

uint8_t uart0_rxbuf_begin;
uint8_t uart0_rxbuf_end;



void uart0_set_baudrate(uint16_t baud) {
  baud = ((uint32_t)(F_CPU))/((uint32_t)baud*16) - 1;
  UBRR0H = (uint8_t)(baud>>8);
  UBRR0L = (uint8_t)(baud&0xff);
}


char uart0_getchar() {
  cli();
  uint8_t result = uart0_rxbuf[uart0_rxbuf_begin];
  if (uart0_rxbuf_end==UART0_RXBUF_SIZE) {
    uart0_rxbuf_end=uart0_rxbuf_begin;
  }
  
  if (++uart0_rxbuf_begin>=UART0_RXBUF_SIZE) {
    uart0_rxbuf_begin=0;
  }
  sei();
  return result;
}


char uart0_putchar(char c) {
  cli();
  uart0_txbuf[uart0_txbuf_end] = c;
  if (++uart0_txbuf_end>=UART0_TXBUF_SIZE) {
    uart0_txbuf_end=0;
  }
  if (uart0_txbuf_end==uart0_txbuf_begin) {
    uart0_txbuf_end=UART0_TXBUF_SIZE;
  }
  // reenable transmit register empty interrupt
  UCSR0B |= _BV(UDRIE0);
  sei();
  return c;
}


static char uart0_tx_getchar() {
  uint8_t result = uart0_txbuf[uart0_txbuf_begin];
  if (uart0_txbuf_end==UART0_TXBUF_SIZE) {
    uart0_txbuf_end=uart0_txbuf_begin;
  }
  
  if (++uart0_txbuf_begin>=UART0_TXBUF_SIZE) {
    uart0_txbuf_begin=0;
  }
  return result;
}


static char uart0_rx_putchar(char c) {
  uart0_rxbuf[uart0_rxbuf_end] = c;
  if (++uart0_rxbuf_end>=UART0_RXBUF_SIZE) {
    uart0_rxbuf_end=0;
  }
  if (uart0_rxbuf_end==uart0_rxbuf_begin) {
    uart0_rxbuf_end=UART0_RXBUF_SIZE;
  }
  return c;
}


void uart0_enable() {
  UCSR0B = _BV(RXCIE0) + _BV(UDRIE0) + _BV(RXEN0) + _BV(TXEN0);
}


void uart0_disable() {
  UCSR0B = 0;
}


ISR(USART0_RX_vect) {
  uint8_t c = UDR0;
  if (!uart0_rxfull()) {
    uart0_rx_putchar(c);
  }
  niboCom_uartInterrupt();
}


ISR(USART0_UDRE_vect) {
  if (!uart0_txempty()) {
    UDR0 = uart0_tx_getchar();
  } else {
    UCSR0B &= ~_BV(UDRIE0);
  }
}


#ifdef __cplusplus
} // extern "C"
#endif


