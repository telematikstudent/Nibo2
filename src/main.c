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
void autoMode()
{
    uint8_t driveStatus = drive_status_all_blocked;
    drive(20);
    driveStatus = checkDriveDirection();
    char output[20] = "";
    sprintf(output, "drive: : %i", driveStatus);
    advDisplay_append_line(output);
    if(driveStatus == drive_status_right_free){
				turn_halfRight();
			}
			else if(driveStatus == drive_status_left_free){
				turn_halfLeft();
			}
			else if(driveStatus == drive_status_all_blocked){
				while(1){
					copro_setTargetRel(-10, -10, 10);
					delay(1000);
					driveStatus = checkDriveDirection();

					if(driveStatus == drive_status_right_free){
						turn_halfRight();
						break;
					}
					else if(driveStatus == drive_status_left_free){
						turn_halfLeft();
						break;
					}
				}
			}
}

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
	spi_init();

	niboCom_init();
	advDisplay_init();
	sound_init();

	//Distanzmessung einschalten
	copro_ir_startMeasure();

	// initialize i2c for communication with nds3
	i2c_init();
	leds_init();

	//Timer-interrupt init
	// set Prescaler 1024
	TCCR2 = ((1<<CS22)|(0<<CS21)|(1<<CS20));
	//enable Timer-Overflow-Interrupt
	TIMSK |= (1<<TOIE2);


	niboStartScout(90);

	//	advDisplay_append_line("Martini!");
	//	advDisplay_append_line("Wartet auf ");
	//	advDisplay_append_line("Eingabe...");

}

int main(void) {

	//Laufzeitvariablen
//	uint8_t status = defaultstatus;
//	uint8_t statusMerker = 0;

//	uint8_t cnt = 0;
//	// true = manueller mode || false = automatischer modus

	uint8_t mode = MODE_MAN;
	uint8_t cmd = niboCom_cmd_none;

	uint8_t *nds_scan;

	initBot();
	copro_stop();



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
			}
			else if((PIND & (1 << PD4)) == 0){
				mode = MODE_MAN;
				advDisplay_append_line("-> Manuell");
				delay(500);
			}

			if(cmd == niboCom_cmd_nds_distance){
				nds_scan = checkObjektsOnDistance(NDS_SCAN_DEG);
				niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
			}
				autoMode();

		}//end auto mode

		//command execution manual mode

		if(cmd == niboCom_cmd_nds_distance){
			nds_scan = checkObjektsOnDistance(NDS_SCAN_DEG);
			niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
		}
		else if(cmd == niboCom_cmd_nibo_drive){
			uint8_t driveStatus = drive_status_front_free;
			while(driveStatus == drive_status_front_free){
				cmd = niboCom_getCMD();
				if(cmd != niboCom_cmd_nibo_stop){
					driveStatus = drive(20);
				}
				if(cmd == niboCom_cmd_nds_distance){
					nds_scan = checkObjektsOnDistance(NDS_SCAN_DEG);
					niboCom_putNDSDistance((180/NDS_SCAN_DEG)+1,nds_scan);
				}
				else{
					copro_stop();
					break;
				}
			}

		}
		else if(cmd == niboCom_cmd_nibo_left){
			turn_left();
		}
		else if(cmd == niboCom_cmd_nibo_halfLeft){
			turn_halfLeft();
		}
		else if(cmd == niboCom_cmd_nibo_halfRight){
			turn_halfRight();
		}
		else if(cmd == niboCom_cmd_nibo_right){
			turn_right();
		}
		else if(cmd == niboCom_cmd_nibo_turn){
			turn_around();
		}

	}
}


