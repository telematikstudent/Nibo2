/**
 ============================================================================
 @file       : Application.c
 @author     : Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 @date	     : Version 0.1
 @brief		 : Main programm for nibo, including the main loop
 ============================================================================
 */

#include "main.h"

int voltageCheck = 0;


/**
 * @brief Timer2 interrupt
 */
ISR(TIMER2_OVF_vect)
{
	checkDistance();

	//2sec
	if((voltageCheck++) >= 120){
		voltageCheck = 0;
		double volt = 0;
		//get currente voltage value
		bot_update();
		//calculate the voltage from adc-value
		volt = 0.0166 * bot_supply -1.19;
		if( volt <= 8.5){
			tone(3000,100);
		}
	}

}

void initBot() {

	bot_init();
	sei();
	advDisplay_init();
	advDisplay_append_line("Martini!");
	advDisplay_append_line("Init:");
	delay(1000);

	spi_init();
	advDisplay_append_line("Motor      OK");
	delay(500);

	niboCom_init();
	advDisplay_append_line("XBEE       OK");
	delay(500);

	sound_init();
	advDisplay_append_line("Audio      OK");
	delay(500);

	copro_ir_startMeasure();
	advDisplay_append_line("Sensoren   OK");
	delay(500);

	ndsScan_init();
	advDisplay_append_line("NDS        OK");
	delay(500);

	leds_init();
	advDisplay_append_line("LEDS       OK");
	delay(500);

	//Timer-interrupt init
	// set Prescaler 1024
	TCCR2 = ((1<<CS22)|(0<<CS21)|(1<<CS20));
	//enable Timer-Overflow-Interrupt
	TIMSK |= (1<<TOIE2);
	advDisplay_append_line("Interrupts OK");




	advDisplay_append_line("Bereit!");
	delay(1000);
	advDisplay_clear();


}

int main(void) {

	uint8_t mode = MODE_MAN;
	uint8_t cmd = niboCom_cmd_none;

	uint8_t *nds_scan;

	initBot();


	while (1) {

		cmd = niboCom_getCMD();
		advDisplay_printVoltage();

		if(cmd == niboCom_cmd_nibo_auto){
			mode = MODE_AUTO;
			advDisplay_append_line("-> Automatik");
		}
		else if((PIND & (1 << PD4)) == 0){
			mode = MODE_AUTO;
			advDisplay_append_line("-> Automatik");
			delay(500);
		}

		//auto mode
		while(mode == MODE_AUTO){

			cmd = niboCom_getCMD();
			advDisplay_printVoltage();

			if(cmd == niboCom_cmd_nibo_man){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				delay(500);
				break;
			}
			else if((PIND & (1 << PD4)) == 0){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				delay(500);
				break;
			}

			if(cmd == niboCom_cmd_nds_distance){
				nds_scan = ndsScan(NDS_SCAN_DEG);
				niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
			}
			autoMode();

		}//end auto mode
		copro_stop();

		//command execution manual mode

		if(cmd == niboCom_cmd_nds_distance){
			nds_scan = ndsScan(NDS_SCAN_DEG);
			niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
		}
		else if(cmd == niboCom_cmd_nibo_drive){
			uint8_t driveStatus = drive_front_free;
			while(driveStatus == drive_front_free){
				cmd = niboCom_getCMD();
				if(cmd != niboCom_cmd_nibo_stop){
					driveStatus = drive(20);
				}
				else{
					copro_stop();
					break;
				}
				if(cmd == niboCom_cmd_nds_distance){
					nds_scan = ndsScan(NDS_SCAN_DEG);
					niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
				}
			}

		}
		else if(cmd == niboCom_cmd_nibo_left){
			drive_turn_left();
		}
		else if(cmd == niboCom_cmd_nibo_halfLeft){
			drive_turn_halfLeft();
		}
		else if(cmd == niboCom_cmd_nibo_halfRight){
			drive_turn_halfRight();
		}
		else if(cmd == niboCom_cmd_nibo_right){
			drive_turn_right();
		}
		else if(cmd == niboCom_cmd_nibo_turn){
			drive_turn_around();
		}

	}
}

void autoMode()
{
    uint8_t driveStatus = drive_all_blocked;
    drive(20);
    driveStatus = drive_getFreePath();

    if(driveStatus == drive_right_free){
		drive_turn_halfRight();
	}
	else if(driveStatus == drive_left_free){
		drive_turn_halfLeft();
	}
	else if(driveStatus == drive_all_blocked){
		while(1){
			copro_setTargetRel(-10, -10, 10);
			delay(1500);
			driveStatus = drive_getFreePath();

			if(drive_isRightFree()){
				copro_stop();
				drive_turn_halfRight();
				break;
			}
			else if(drive_isLeftFree()){
				copro_stop();
				drive_turn_halfLeft();
				break;
			}
		}
	}
}


void checkDistance(){
	copro_update();
	if((copro_distance[0]/256) > irAbstand){leds_set_status(LEDS_RED,7);}
	else{leds_set_status(LEDS_GREEN,7);}

	if((copro_distance[1]/256) > irAbstand){leds_set_status(LEDS_RED,6);}
	else{leds_set_status(LEDS_GREEN,6);}

	if((copro_distance[2]/256) > irAbstand){leds_set_status(LEDS_RED,5);leds_set_status(LEDS_RED,4);}
	else{leds_set_status(LEDS_GREEN,5);leds_set_status(LEDS_GREEN,4);}

	if((copro_distance[3]/256) > irAbstand){leds_set_status(LEDS_RED,3);}
	else{leds_set_status(LEDS_GREEN,3);}

	if((copro_distance[4]/256) > irAbstand){leds_set_status(LEDS_RED,2);}
	else{leds_set_status(LEDS_GREEN,2);}

}


