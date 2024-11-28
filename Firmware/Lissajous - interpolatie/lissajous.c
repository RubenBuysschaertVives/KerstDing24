#include "lissajous.h"
#include "stm32f091xc.h"
#include "dac.h"

//void DrawLissajous(Lissajous* lissajous, uint8_t startIndex, uint8_t count, uint8_t pointInterval)
//{
//	uint8_t i;
//	
//	for(i = startIndex; i < (startIndex + count); i++)
//	{
//		SetDacX(lissajous->points[i].x);
//		SetDacY(lissajous->points[i].y);
//		WaitForMs(pointInterval);
//	}
//}
