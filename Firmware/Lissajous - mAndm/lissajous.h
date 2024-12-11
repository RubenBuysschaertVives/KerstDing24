#include "stm32f091xc.h"
#include "stdbool.h"

#if !defined(LISSAJOUS_DEFINED)
	#define LISSAJOUS_DEFINED
	
	#define MAX_NUMBER_OF_POINTS 500		// Maximum aantal (hoek)punten waaruit een Lissajous-figuur mag bestaan.
																			// Let op: dit is niet gelijk aan de beeldresolutie. Die wordt bepaald door de 
																			// DA-converter en is 12-bit, dus 4096...
																			
	#define INTERPOLATION_STEP_SIZE 10	// Hoe kleiner de stappen, hoe langer het duurt voor het renderen van een volledige figuur.
																			// Zoek een evenwicht tussen details in beeld en verversingsfrequentie.
	
	typedef struct{
		uint16_t x;
		uint16_t y;
		bool suppressPreviousTrack;				// Als het pad naar dit punt niet getekend moet worden, zet hier true. Anders false.
	}Point;
	
	typedef struct{
		Point points[MAX_NUMBER_OF_POINTS];
		uint16_t length;									// Geeft aan hoeveel punten er getekend moeten worden.
	}Lissajous;
	
	void DrawLissajous(Lissajous* lissajousXmas, uint16_t count);
#endif
