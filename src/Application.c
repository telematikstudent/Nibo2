/**
 ============================================================================
 @file       : Application.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 0.1
 @brief		 : Main programm for nibo including nibo initialization and the main loop
 ============================================================================
 */

/**
 * includes
 */
#include "Application.h"

/**
 * vars
 */

int timer_counter = timer_limit;




/**
 * @brief Timer2 interrupt
 */
ISR(TIMER2_OVF_vect)
{
	int i = 0;

	//check voltage
	if(timer_counter++ >= timer_limit){
		advDisplay_printVoltage();
		timer_counter = 0;

	}
	checkDistance();


}


void checkDistance(){
	copro_update();
	if((copro_distance[0]/256) > ir_sensor_limit){leds_set_status(LEDS_RED,7);}
	else{leds_set_status(LEDS_GREEN,7);}

	if((copro_distance[1]/256) > ir_sensor_limit){leds_set_status(LEDS_RED,6);}
	else{leds_set_status(LEDS_GREEN,6);}

	if((copro_distance[2]/256) > ir_sensor_limit){leds_set_status(LEDS_RED,5);leds_set_status(LEDS_RED,4);}
	else{leds_set_status(LEDS_GREEN,5);leds_set_status(LEDS_GREEN,4);}

	if((copro_distance[3]/256) > ir_sensor_limit){leds_set_status(LEDS_RED,3);}
	else{leds_set_status(LEDS_GREEN,3);}

	if((copro_distance[4]/256) > ir_sensor_limit){leds_set_status(LEDS_RED,2);}
	else{leds_set_status(LEDS_GREEN,2);}

}

void initNibo(){
	bot_init();

	sei();
	spi_init();


	advDisplay_init();

	sound_init();

	pwm_init();
	leds_init();

	copro_ir_startMeasure();

	leds_set_displaylight(50);

	//Timer-interrupt init
	// set Prescaler 1024
	TCCR2 = ((1<<CS22)|(0<<CS21)|(1<<CS20));
	//enable Timer-Overflow-Interrupt
	TIMSK |= (1<<TOIE2);


}





/**
 *
 * @return returns always 0
 */
int main(void){

	initNibo();

	while(1){
		advDisplay_clear();
		delay(100);
		advDisplay_append_line("Martini!");
		delay(1000);
	}
	return 0;
}
