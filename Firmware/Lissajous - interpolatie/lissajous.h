#include "stm32f091xc.h"
#include "stdbool.h"

#if !defined(LISSAJOUS_DEFINED)
	#define LISSAJOUS_DEFINED
	
	#define MAX_NUMBER_OF_POINTS 500		// Maximum aantal (hoek)punten waaruit een Lissajous-figuur
																			// mag bestaan.
																			// Let op: dit is niet gelijk aan de beeld-
																			// resolutie. Die wordt bepaald door de 
																			// DA-converter en is 12-bit, dus 4096...
	
	typedef struct{
		uint16_t x;
		uint16_t y;
		bool suppressPreviousTrack;				// Als het pad naar dit punt niet getekend moet worden, zet hier true. Anders false.
	}Point;
	
	typedef struct{
		Point points[MAX_NUMBER_OF_POINTS];
		uint16_t length;									// Geeft aan hoeveel punten er getekend moeten worden.
	}Lissajous;
	
	//void DrawLissajous(Lissajous* lissajous, uint8_t startIndex, uint8_t count, uint8_t pointInterval);
#endif
