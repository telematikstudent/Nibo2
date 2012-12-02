/**
 * @file		main.c
 * @author		Phillip Kopprasch, Marcus Tenbusch, Christian Witte
 * @date		Version 0.1
 * @brief		Main program for nibo, including the main loop.
 */

#include "main.h"

//counter for the voltage-check interval
int voltageCheck = 0;

//current mode
uint8_t mode = MODE_MAN;


//nds3 measurement
uint8_t *nds_scan;

/**
 * @brief Timer2 interrupt ~60Hz
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

/**
 * @brief initializes the nibo
 */
void initBot() {

	bot_init();
	sei();

	//display init
	advDisplay_init();
	advDisplay_printVoltage();
	advDisplay_append_line("Martini!");
	advDisplay_append_line("Init...");
	delay(1000);

	//copro init
	spi_init();
	advDisplay_append_line("Motor      OK");
	delay(500);

	//niboCom init
	niboCom_init();
	advDisplay_append_line("XBEE       OK");
	delay(500);

	//sound init
	sound_init();
	advDisplay_append_line("Audio      OK");
	delay(500);

	//ir sensor init
	copro_ir_startMeasure();
	advDisplay_append_line("Sensoren   OK");
	delay(500);

	//nds3 init
	ndsScan_init();
	advDisplay_append_line("NDS        OK");
	delay(500);

	//led init
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

/**
 * @brief the main function contains the main-loop
 */
int main() {

	//current cmd
	uint8_t cmd = niboCom_cmd_none;

	initBot();


	while (1) {

		//catch command via xbee
		cmd = niboCom_getCMD();
		advDisplay_printVoltage();

		//check whether mode has to be changed or not
		if(cmd == niboCom_cmd_nibo_auto){
			mode = MODE_AUTO;
			advDisplay_append_line("-> Automatik");
		}
		//Button S3
		else if((PIND & (1 << PD4)) == 0){
			mode = MODE_AUTO;
			advDisplay_append_line("-> Automatik");
			delay(500);
		}

		//auto mode loop
		while(mode == MODE_AUTO){
			//check for new commands via xbee
			cmd = niboCom_getCMD();
			advDisplay_printVoltage();

			//check whether mode has to be changed or not
			if(cmd == niboCom_cmd_nibo_man){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				copro_stop();
				break;
			}
			//Button S3
			else if((PIND & (1 << PD4)) == 0){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				copro_stop();
				delay(500);
				break;
			}
			//command nds scan
			if(cmd == niboCom_cmd_nds_distance){
				nds_scan = ndsScan(NDS_SCAN_DEG);
				niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
			}

			//drive around ;-)
			autoMode();

		}//end auto mode loop


		//manual mode -> command execution

		//command nds scan
		if(cmd == niboCom_cmd_nds_distance){
			nds_scan = ndsScan(NDS_SCAN_DEG);
			niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
		}
		//command drive until obstacle
		else if(cmd == niboCom_cmd_nibo_drive){
			uint8_t driveStatus = drive_front_free;
			//drive loop
			while(driveStatus == drive_front_free){
				//check for new commands via xbee
				cmd = niboCom_getCMD();
				//command is not stop-command
				if(cmd != niboCom_cmd_nibo_stop){
					driveStatus = drive(20);
				}
				//command stop
				else{
					copro_stop();
					break;
				}
				//command nds scan
				if(cmd == niboCom_cmd_nds_distance){
					nds_scan = ndsScan(NDS_SCAN_DEG);
					niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
				}
			}//end drive loop

		}
		//command turn left
		else if(cmd == niboCom_cmd_nibo_left){
			drive_turn_left();
		}
		//command turn half left
		else if(cmd == niboCom_cmd_nibo_halfLeft){
			drive_turn_halfLeft();
		}
		//command turn right
		else if(cmd == niboCom_cmd_nibo_halfRight){
			drive_turn_halfRight();
		}
		//command turn half right
		else if(cmd == niboCom_cmd_nibo_right){
			drive_turn_right();
		}
		//command turn around
		else if(cmd == niboCom_cmd_nibo_turn){
			drive_turn_around();
		}

	}
}

/**
 * @brief moves the nibo around automagically
 */
void autoMode(){
	uint8_t cmd = niboCom_cmd_none;
    uint8_t driveStatus = drive_all_blocked;
    //try to drive forward
    drive(20);
    //get path for the nibo
    driveStatus = drive_getFreePath();

    //front is blocked but right is free
    if(driveStatus == drive_right_free){
		drive_turn_halfRight();
	}
    //front is blocked but left is free
	else if(driveStatus == drive_left_free){
		drive_turn_halfLeft();
	}
    //front, right and left side of the nibo are blocked
	else if(driveStatus == drive_all_blocked){
		//drive backwarts loop
		while(1){

			//check for new commands via xbee
			cmd = niboCom_getCMD();
			advDisplay_printVoltage();

			//check whether mode has to be changed or not
			if(cmd == niboCom_cmd_nibo_man){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				copro_stop();
				break;
			}
			//Button S3
			else if((PIND & (1 << PD4)) == 0){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				copro_stop();
				delay(500);
				break;
			}
			//command nds scan
			if(cmd == niboCom_cmd_nds_distance){
				nds_scan = ndsScan(NDS_SCAN_DEG);
				niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
			}

			//drive backwarts
			copro_setTargetRel(-10, -10, 10);
			delay(1500);

			//turn right if free
			if(drive_isRightFree()){
				copro_stop();
				drive_turn_halfRight();
				break;
			}
			//turn left if free
			else if(drive_isLeftFree()){
				copro_stop();
				drive_turn_halfLeft();
				break;
			}
		}
	}
}

/**
 * @brief checks the values of the IR-sensors and switches the leds depending on the value.
 */
void checkDistance(){
	copro_update();

	//right
	if((copro_distance[0]/256) > IRDistance){leds_set_status(LEDS_RED,7);}
	else{leds_set_status(LEDS_GREEN,7);}

	//half right
	if((copro_distance[1]/256) > IRDistance){leds_set_status(LEDS_RED,6);}
	else{leds_set_status(LEDS_GREEN,6);}

	//front
	if((copro_distance[2]/256) > IRDistance){leds_set_status(LEDS_RED,5);leds_set_status(LEDS_RED,4);}
	else{leds_set_status(LEDS_GREEN,5);leds_set_status(LEDS_GREEN,4);}

	//half left
	if((copro_distance[3]/256) > IRDistance){leds_set_status(LEDS_RED,3);}
	else{leds_set_status(LEDS_GREEN,3);}

	//left
	if((copro_distance[4]/256) > IRDistance){leds_set_status(LEDS_RED,2);}
	else{leds_set_status(LEDS_GREEN,2);}

}
