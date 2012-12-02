/*
 ============================================================================
 Name        : n2sound.h
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Funktionen zur Erzeugung einfacher Melodien auf dem Nibo
 ============================================================================
 */

#ifndef N2SOUND_H_
#define N2SOUND_H_

#include <nibo/niboconfig.h>
#include <nibo/bot.h>
#include <nibo/iodefs.h>
#include <nibo/sound.h>

#include <nibo/delay.h>

// Definiert gerundete Frequenzen fuer die angegebenen Toene

#define C4 262
#define C4SHARP 277
#define D4 294
#define D4SHARP 311
#define E4 330
#define F4 349
#define F4SHARP 370
#define G4 392
#define G4SHARP 415
#define A4 440
#define A4SHARP 466
#define B4 494
#define C5 523
#define C5SHARP 554
#define D5 587
#define D5SHARP 622
#define E5 659
#define F5 698
#define F5SHARP 740
#define G5 784
#define G5SHARP 831
#define A5 880
#define A5SHARP 932
#define B5 988
#define C6 1047
#define C6SHARP 1109
#define D6 1175
#define D6SHARP 1245
#define E6 1319
#define F6 1397
#define F6SHARP 1480
#define G6 1568
#define G6SHARP 1661
#define A6 1760
#define A6SHARP 1865
#define B6 1976
#define C7 2093
#define C7SHARP 2218
#define D7 2349
#define D7SHARP 2489
#define E7 2637
#define F7 2794
#define F7SHARP 2960
#define G7 3136
#define G7SHARP 3322
#define A7 3520
#define A7SHARP 3729
#define B7 3951
#define C8 4186


/**
 * Spielt einen Ton ab.
 * frequency ist die Frequenz des Tons in Hz (nicht hoeher als 5000 uebergeben!)
 * duration gibt die Wiedergabedauer des Tons an
 */
int tone(int frequency, int duration);

#endif /* N2SOUND_H_ */
