 #include "showParameter.h"
#include "fahren.h"

void showParameter(uint8_t status, uint8_t richtung, uint8_t winkel, uint8_t distance){
	char output[21] = "";

	gfx_fill(0);

	//Anzeige der der einzelnen Schritten
	sprintf(output, "Ticks l: %3i  r: %3i", copro_ticks_l, copro_ticks_r);
	gfx_move(0, 0);
	gfx_print_text(output);

	//Anzeige der Geschwindigkeit
	sprintf(output, "Speed l: %3i  r: %3i", copro_speed_l, copro_speed_r);
	gfx_move(0, 10);
	gfx_print_text(output);

	//Anzeige der Sensoren 1 , 2, 3, 4, 5
	sprintf(output, "%3i %3i %3i %3i %3i", copro_distance[0] / 256,
			copro_distance[1] / 256, copro_distance[2] / 256,
			copro_distance[3] / 256, copro_distance[4] / 256);
	gfx_move(0, 20);
	gfx_print_text(output);

	//Anzeige des Status
	sprintf(output, "status: %1i", status);
	gfx_move(0, 30);
	gfx_print_text(output);

	//Anzeige der belegten richtungen
	sprintf(output, "belegt: %3i", richtung);
	gfx_move(0, 40);
	gfx_print_text(output);

	//Anzeige Winkel und Dinstanz NDS
	sprintf(output, "Winkel :%3i NDS: %3i ", winkel, distance);
	gfx_move(0, 50);
	gfx_print_text(output);

	delay(100);
}

void showPoints(uint8_t points[], uint8_t cnt){

		char output[21] = "";

		gfx_fill(0);

		//Anzeige der der einzelnen Schritten
		sprintf(output, "test1: %3i", points[1]);
		gfx_move(0, 0);
		gfx_print_text(output);

}
