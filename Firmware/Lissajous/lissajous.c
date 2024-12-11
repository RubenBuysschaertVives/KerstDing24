#include "lissajous.h"
#include "stm32f091xc.h"
#include "dac.h"
#include "lissajous.h"

// Afstand tussen twee punten berekenen en interpoleren...
void DrawLissajous(Lissajous* lissajous, uint16_t count)
{
	// yt = a * dx + y0 of xt = dy/a + x0
	float a, xt, yt, y0;
	uint16_t i, j;
	
	// Alle punten overlopen.
	for(i = 0; i < (count - 1); i++)
	{
		// Track naar nieuwe punt tekenen of onderdrukken?
		if(lissajous->points[i+1].suppressPreviousTrack == false)
		{
			// Track tekenen (lineair interpoleren).
			// Vergelijking van de rechte tussen de twee punten zoeken.
			if(lissajous->points[i].x != lissajous->points[i+1].x)
			{
				// Geen verticale rechte.
				// Richtingscoëfficient berekenen voor de formule: y = a.dx + y0.
				// Als je de y wil laten variëren, dan moet je deze formule gebruiken: x = dy/a + x0.
				a = (float)(lissajous->points[i+1].y - lissajous->points[i].y)/(float)(lissajous->points[i+1].x - lissajous->points[i].x);
				
				// Gaat het over een hellingsgraad van minder dan of meer dan 45°?
				if((a > -1) && (a < 1))
				{
					// De hoek is minder scherp dan 45°, laat x variëren voor betere nauwkeurigheid.
					if(lissajous->points[i].x < lissajous->points[i+1].x)
					{
						// Tweede punt ligt verder van de oorsprong dan het eerste.					
						for(j = lissajous->points[i].x; j <= (lissajous->points[i+1].x - INTERPOLATION_STEP_SIZE); j +=INTERPOLATION_STEP_SIZE)
						{
							xt = j;
							SetDacX((uint16_t)xt);
							
							// yt = a * dx + y0;
							yt = a * (xt - lissajous->points[i].x) + lissajous->points[i].y;
							SetDacY((uint16_t)yt);
						}
					}
					else
					{
						// Tweede punt ligt dichter bij de oorsprong dan het eerste.
						for(j = lissajous->points[i].x; j >= (lissajous->points[i+1].x + INTERPOLATION_STEP_SIZE); j-=INTERPOLATION_STEP_SIZE)
						{
							xt = j;
							SetDacX((uint16_t)xt);
							
							// yt = a * dx + y0;
							yt = a * (xt - lissajous->points[i].x) + lissajous->points[i].y;
							SetDacY((uint16_t)yt);
						}
					}				
				}
				else
				{
					// De hoek is scherper dan 45°, laat y variëren voor betere nauwkeurigheid.
					if(lissajous->points[i].y < lissajous->points[i+1].y)
					{
						// Eerste punt ligt dichter bij de oorsprong dan tweede.					
						for(j = lissajous->points[i].y; j <= (lissajous->points[i+1].y - INTERPOLATION_STEP_SIZE); j+=INTERPOLATION_STEP_SIZE)
						{
							yt = j;
							SetDacY((uint16_t)yt);							
							
							// xt = dy/a + x0
							xt = (yt - lissajous->points[i].y)/a + lissajous->points[i].x;
							SetDacX((uint16_t)xt);						
						}
					}
					else
					{
						// Tweede punt ligt dichter bij de oorsprong dan eerste.
						for(j = lissajous->points[i].y; j >= (lissajous->points[i+1].y + INTERPOLATION_STEP_SIZE); j-=INTERPOLATION_STEP_SIZE)
						{
							yt = j;
							SetDacY((uint16_t)yt);
							
							// xt = dy/a + x0
							xt = (yt - lissajous->points[i].y)/a + lissajous->points[i].x;
							SetDacX((uint16_t)xt);	
						}
					}
				}			
			}
			else
			{
				// Verticale rechte...
				if(lissajous->points[i].y < lissajous->points[i+1].y)
				{
					// Eerste punt ligt dichter bij de oorsprong dan tweede (stijgen).
					// Ga stap voor stap naar de volgende Y-coördinaat via increments.
					for(j = lissajous->points[i].y; j <= (lissajous->points[i+1].y - INTERPOLATION_STEP_SIZE); j+=INTERPOLATION_STEP_SIZE)
					{
						// X-coördinaat blijft constant.
						xt = lissajous->points[i].x;
						SetDacX((uint16_t)xt);
						
						// Y-coördinaat evolueert.
						yt = j;
						SetDacY((uint16_t)yt);
					}	
				}			
				else
				{
					// Tweede punt ligt dichter bij de oorsprong dan eerste (dalen).
					// Ga stap voor stap naar de volgende Y-coördinaat via decrements.
					for(j = lissajous->points[i].y; j >= (lissajous->points[i+1].y + INTERPOLATION_STEP_SIZE); j-=INTERPOLATION_STEP_SIZE)
					{
						// X-coördinaat blijft constant.
						xt = lissajous->points[i].x;
						SetDacX((uint16_t)xt);
						
						// Y-coördinaat evolueert.
						yt = j;
						SetDacY((uint16_t)yt);
					}	
				}
			}
		}
	}
}
