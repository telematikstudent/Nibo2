/**
 ============================================================================
 @file       : Application.c
 @author     : Phillip Kopprasch
 @date	     : Version 0.1
 @brief		 : Main programm for nibo including nibo initialization and the main loop
 ============================================================================
 */

/**
 * includes
 */
#include "Application.h"


/**
 * @brief Timer2 interrupt
 */
ISR(TIMER2_OVF_vect)
{
	checkDistance();
}


void checkDistance(){

	bool obstacle = false;
	copro_update();

	//left
	if((copro_distance[0]/256) > ir_sensor_limit){
		leds_set_status(LEDS_RED,7);
		obstacle = true;
	}
	else leds_set_status(LEDS_GREEN,7);

	//half left
	if((copro_distance[1]/256) > ir_sensor_limit){
		leds_set_status(LEDS_RED,6);
		obstacle = true;
	}
	else leds_set_status(LEDS_GREEN,6);

	//front
	if((copro_distance[2]/256) > ir_sensor_limit){
		leds_set_status(LEDS_RED,5);leds_set_status(LEDS_RED,4);
		obstacle = true;
	}
	else{
		leds_set_status(LEDS_GREEN,5);
		leds_set_status(LEDS_GREEN,4);
	}

	//half right
	if((copro_distance[3]/256) > ir_sensor_limit){
		leds_set_status(LEDS_RED,3);
		obstacle = true;
	}
	else leds_set_status(LEDS_GREEN,3);

	//right
	if((copro_distance[4]/256) > ir_sensor_limit){
		leds_set_status(LEDS_RED,2);
		obstacle = true;
	}
	else leds_set_status(LEDS_GREEN,2);


//	if(obstacle) copro_stop();
//	else copro_setSpeed(14,14);

}

void initNibo(){
	bot_init();

	sei();
	spi_init();

	sound_init();

	pwm_init();
	leds_init();

	copro_ir_startMeasure();

	i2c_init();

	//Martini libs
	advDisplay_init();

	niboCom_init();


	//Timer-interrupt init
	// set Prescaler 1024
	TCCR2 = ((1<<CS22)|(0<<CS21)|(1<<CS20));
	//enable Timer-Overflow-Interrupt
	TIMSK |= (1<<TOIE2);

	//leds_set_status_intensity(128);

	advDisplay_append_line("Initialisiert!");
}


/**
 *
 * @return returns always 0
 */
int main(void){

	initNibo();

//	int i = 0;
//	char output[14] = "";
//
//	uint8_t c = 'a';
//	int char_count = 0;

	while(1){
//		c = niboCom_getchar();
//		if( (char)c != 0){
//
//
//			if((char)c == '\r' || char_count >= 13){
//				niboCom_putchar('\n');
//				niboCom_putchar('\r');
//				output[char_count] = '\0';
//				strcpy(output, output);
//				advDisplay_append_line(output);
//				char_count = 0;
//			}
//			else{
//				niboCom_putchar((char)c);
//				output[char_count++] = (char)c;
//			}
//
//		}

		//niboCom_putIRDistance(copro_distance);


		delay(1000);
		advDisplay_printVoltage();

	}
	return 0;
}








