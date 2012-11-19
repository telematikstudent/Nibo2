
#include "initBot.h"

//veraltet!
void initBot() {

	bot_init();
	sei();
	spi_init();

	niboCom_init();
	advDisplay_init();

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

	advDisplay_append_line("Martini!");
	advDisplay_append_line("Wartet auf ");
	advDisplay_append_line("Eingabe...");

}

uint8_t reset(uint8_t LastStatus,uint8_t status) {
	//resett des Tickzeahlers
	if (LastStatus != status) {
		copro_resetOdometry(0, 0);
	}
	//Überprüfen des Buttons
	if (PIND & (1 << PD4)) {
		return status;
	} else {
		void advDisplay_clear();
		return rueckWende;
	}


}
