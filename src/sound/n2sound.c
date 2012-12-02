/*
 ============================================================================
 Name        : n2sound.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Funktionen zur Erzeugung einfacher Melodien auf dem Nibo
 ============================================================================
 */


#include <nibo/niboconfig.h>
#include <nibo/bot.h>
#include <nibo/iodefs.h>
#include <nibo/sound.h>

#include "n2sound.h"

/**
 * Spielt einen Ton ab
 * Vor der ersten Benutzung einmal sound_init() aufrufen (deklariert in nibo/sound.h)
 * frequency ist die Frequenz des Tons in Hz (nicht hoeher als 5000 uebergeben!)
 * duration gibt die Wiedergabedauer des Tons an
 */
int tone(int frequency, int duration) {
	int interval = (50000 / frequency);
	duration = duration * 100;

	while (duration) {
		int i = interval;
		clear_output_bit(IO_AUDIO);
		while (duration && i) {
			duration--;
			i--;
			delay_us(10);
		}
		i = interval;
		set_output_bit(IO_AUDIO);
		while (duration && i) {
			duration--;
			i--;
			delay_us(10);
		}

	}

	return 1;
}
