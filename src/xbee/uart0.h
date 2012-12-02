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

/*! @file    uart0.h
 *  @brief   Routinen zur Kommunikation über die serielle Schnittstelle
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2008-07-30
 */

#ifndef NIBO_UART0_H_
#define NIBO_UART0_H_
#if defined(NIBO_USE_UART0) || defined (DOXYGEN)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART0_TXBUF_SIZE 200
#define UART0_RXBUF_SIZE 50

/*!
 * Setzt neue Baudrate
 */
void uart0_set_baudrate(uint16_t baud);

extern uint8_t uart0_txbuf[UART0_TXBUF_SIZE];
extern uint8_t uart0_rxbuf[UART0_RXBUF_SIZE];

extern uint8_t uart0_txbuf_begin;
extern uint8_t uart0_txbuf_end;

extern uint8_t uart0_rxbuf_begin;
extern uint8_t uart0_rxbuf_end;

/*!
 * Senden und empfangen aktivieren.
 */
void uart0_enable();

/*!
 * Senden und empfangen deaktivieren.
 */
void uart0_disable();


/*!
 * Gibt ein einzelnes Zeichen aus dem Empfangspuffer zurück.
 * Darf nur aufgerufen werden wenn (uart0_rxempty()==false) ist.
 */
char uart0_getchar();


/*!
 * Schreibt ein einzelnes Zeichen in den Sendepuffer.
 * Darf nur aufgerufen werden solange (uart0_txfull()==false) ist.
 */
char uart0_putchar(char c);


/*!
 * Liefert true wenn der Empfangspuffer leer ist.
 */
static inline char uart0_rxempty() {
  return uart0_rxbuf_begin==uart0_rxbuf_end;
}


/*!
 * Liefert true wenn der Sendepuffer leer ist.
 */
static inline char uart0_txempty() {
  return uart0_txbuf_begin==uart0_txbuf_end;
}


/*!
 * Liefert true wenn der Empfangspuffer voll ist.
 */
static inline char uart0_rxfull() {
  return uart0_rxbuf_end==UART0_RXBUF_SIZE;
}


/*!
 * Liefert true wenn der Sendepuffer voll ist.
 */
static inline char uart0_txfull() {
  return uart0_txbuf_end==UART0_TXBUF_SIZE;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NIBO_USE_UART0
#endif // NIBO_UART0_H_
