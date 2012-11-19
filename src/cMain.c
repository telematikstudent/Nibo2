/**
 ============================================================================
 @file       : Application.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 0.1
 @brief		 : Main programm for nibo, including the main loop
 ============================================================================
 */

#include "fahren.h"
#include "scout.h"
#include "showParameter.h"
#include "initBot.h"

/**
 * @brief Timer2 interrupt
 */
ISR(TIMER2_OVF_vect)
{

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

int main(void) {

	//Laufzeitvariablen
	uint8_t status = 5;
	uint8_t statusMerker = 0;
	uint8_t *points;
	uint8_t cnt = 0;

	initBot();

	while (1 == 1) {
		//um zustandsänderungen aufzunehmen
		statusMerker = status;

		if(cnt++ == 200){
			advDisplay_printVoltage();
		}

//testanzeige fürs fahren

//		char output[21] = "";
//
//		gfx_fill(0);
//
//		//Anzeige der der einzelnen Schritten
//		sprintf(output, "Ticks l: %3i  r: %3i", copro_ticks_l, copro_ticks_r);
//		gfx_move(0, 0);
//		gfx_print_text(output);
//
//		//Anzeige der Geschwindigkeit
//		sprintf(output, "Speed l: %3i  r: %3i", copro_speed_l, copro_speed_r);
//		gfx_move(0, 10);
//		gfx_print_text(output);
//
//		//Anzeige der Sensoren 1 , 2, 3, 4, 5
//		sprintf(output, "%3i %3i %3i %3i %3i", copro_distance[0] / 256,
//				copro_distance[1] / 256, copro_distance[2] / 256,
//				copro_distance[3] / 256, copro_distance[4] / 256);
//		gfx_move(0, 20);
//		gfx_print_text(output);
//
//		//Anzeige des Status
//		sprintf(output, "status: %1i", status);
//		gfx_move(0, 30);
//		gfx_print_text(output);
//		delay(200);

		switch (status) {
		case fahren:
			status = drive(12);
			break;
		case rueckWende:
			status = wenden(checkDriveDirection());
			break;
		case scout:
			points = checkObjektsOnDistance(2);
			niboCom_putPackage(0,90,points);
			status = 5;
			break;
		case 5 :
			status = reset(statusMerker, status);
			break;
		}
	}
}
