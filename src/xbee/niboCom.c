/**
 * @file		niboCom.c
 * @author		Phillip Kopprasch
 * @date		Version 0.1
 * @brief		library for nibo2pc communication.
 */
#include "niboCom.h"


/**
 * status var for receiving
 */
bool startSignReceived = false;

/**
 * last command received via xbee
 */
uint8_t lastCMD = niboCom_cmd_none;

/**
 * rx buffer for current packet
 */
uint8_t buffer[niboCom_bufferSize];

/**
 * index of the first free space in
 */
uint8_t bufferPos = 0;

/**
 *@brief initializes xbee communication
 */
void niboCom_init(){
	uart0_set_baudrate(niboCom_default_baudrate);
	uart0_enable();
}

/**
 * @brief sends a char via xbee. Blocking function.
 * @param c char to send
 */
void niboCom_putchar(uint8_t c){
	while(uart0_txfull() == true);
	uart0_putchar(c);
	delay(2);
}

/**
 * @brief tries receive a char via xbee. Non-Blocking function.
 * @return a received char or zero if no char was received
 */
uint8_t niboCom_getchar(){
	if(uart0_rxempty()==false) return uart0_getchar();
	return 0;
}

/**
 * @brief sends a niboCom packet via xbee
 * @param cmd the command type of the packet
 * @param size the size of the data part of the packet
 * @param datathe data part of the packet
 */
void niboCom_putPacket(uint8_t cmd, uint8_t size, uint8_t *data){
	int i = 0;

	//startsign
	niboCom_putchar(0x68);

	niboCom_putchar(cmd);
	niboCom_putchar(size);
	for(i = 0; i < size;i++){
		niboCom_putchar(data[i]);
	}
	//endsign
	niboCom_putchar(0x16);
}

/**
 * @brief sends a IRDistance packet via xbee
 * @param data the values of the ir sensors
 */
void niboCom_putIRDistance(uint16_t *data){
	int i = 0;
	uint8_t distance[5];
	//scale values from uint16_t down to uint8_t
	for(i = 0; i < 5;i++){
		distance[i] = data[i]/256;
	}

	niboCom_putPacket(niboCom_cmd_ir_distance,5, distance);
}

/**
 * @brief sends a NDSDistance packet via xbee
 * @param size the number of nds values
 * @param data the nds measurement values
 */
void niboCom_putNDSDistance(uint8_t size, uint8_t *data){
	niboCom_putPacket(niboCom_cmd_nds_distance,size, data);
}

/**
 * @brief sends a DirectionChange packet via xbee
 * @param direction the direction change the nibo made
 */
void niboCom_putDircetionChange(uint8_t direction){
	niboCom_putPacket(direction,0,0);
}

/**
 * @brief sends a Distance packet via xbee
 * @param ticks the number of ticks the nibo moved
 */
void niboCom_putDistance(uint8_t ticks){
	niboCom_putPacket(niboCom_cmd_nibo_distance,1,&ticks);
}

/**
 * @brief tries to catch a command send via xbee
 * @return the last command received via xbee or
 * niboCom_cmd_none(0) if no new command was received
 */
uint8_t niboCom_getCMD(){

	uint8_t tmp = lastCMD;
	if(tmp != niboCom_cmd_none){
		lastCMD = niboCom_cmd_none;
	}

	return tmp;
}

/**
 * @brief is called on the USART0_RX_vect interrupt,
 * receives char send via xbee and tries to recognize niboCom packets
 */
void niboCom_uartInterrupt(){
	//wait until rx buffer is not empty
	while(uart0_rxempty() == true);
	uint8_t c = niboCom_getchar();

	//wait for startsign
	if(c == 0x68){
		startSignReceived = true;
	}
	else if(startSignReceived != true){
		return;
	}
	//fill buffer
	buffer[bufferPos++] = c;

	//check wheter the 4th char is the endsign or not
	if(bufferPos == 4){
		bufferPos = 0;
		startSignReceived = false;
		if(c == 0x16){
			lastCMD = buffer[1];
		}
	}

}
