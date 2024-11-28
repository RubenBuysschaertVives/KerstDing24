//#define VIVES
#define KERSTBOOM
#define INTERPOLATION_STEP_SIZE 10			// TODO: Zo laag mogelijk houden. Nog verder testen.

#include "stm32f091xc.h"
#include "stdio.h"
#include "stdbool.h"
#include "usart2.h"
#include "dac.h"
#include "lissajous.h"

void SystemClock_Config(void);
void WaitForMs(uint32_t timespan);
void DrawLissajous(Lissajous* lissajous, uint16_t startIndex, uint16_t count);
//void Delay(void);

// TODO: variabelen opkuisen.
uint16_t count = 0, i = 0;
volatile uint32_t ticks = 0;
char text[101];
Lissajous lissajous;
float a, xt, yt, y0;			// yt = a * dx + y0 of xt = dy/a + x0

int main(void)
{
	SystemClock_Config();
	InitUsart2(9600);
	InitDAC();
	
	sprintf(text, "KerstDing24 - Lissajous figuren via DAC's op een Nucleo-F091RC.\r\n");
	StringToUsart2(text);
	
	// Analoge spanningen op nul volt zetten.
	SetDacX(0);
	SetDacY(0);
	
	// Data initialiseren op nul.
	for(i = 0; i < MAX_NUMBER_OF_POINTS; i++)
	{
		lissajous.points[i].x = 0;
		lissajous.points[i].y = 0;
		lissajous.points[i].suppressPreviousTrack = false;
	}
		
	#if defined(VIVES)
	{
		lissajous.points[0].x = 2024;
		lissajous.points[0].y = 434;
		lissajous.points[0].suppressPreviousTrack = false;
		lissajous.points[1].x = 1960;
		lissajous.points[1].y = 434;
		lissajous.points[1].suppressPreviousTrack = false;
		lissajous.points[2].x = 1896;
		lissajous.points[2].y = 453;
		lissajous.points[2].suppressPreviousTrack = false;
		lissajous.points[3].x = 1819;
		lissajous.points[3].y = 504;
		lissajous.points[3].suppressPreviousTrack = false;
		lissajous.points[4].x = 1762;
		lissajous.points[4].y = 562;
		lissajous.points[4].suppressPreviousTrack = false;
		lissajous.points[5].x = 885;
		lissajous.points[5].y = 1432;
		lissajous.points[5].suppressPreviousTrack = false;
		lissajous.points[6].x = 808;
		lissajous.points[6].y = 1528;
		lissajous.points[6].suppressPreviousTrack = false;
		lissajous.points[7].x = 718;
		lissajous.points[7].y = 1650;
		lissajous.points[7].suppressPreviousTrack = false;
		lissajous.points[8].x = 674;
		lissajous.points[8].y = 1714;
		lissajous.points[8].suppressPreviousTrack = false;
		lissajous.points[9].x = 597;
		lissajous.points[9].y = 1861;
		lissajous.points[9].suppressPreviousTrack = false;
		lissajous.points[10].x = 552;
		lissajous.points[10].y = 1963;
		lissajous.points[10].suppressPreviousTrack = false;
		lissajous.points[11].x = 520;
		lissajous.points[11].y = 2078;
		lissajous.points[11].suppressPreviousTrack = false;
		lissajous.points[12].x = 501;
		lissajous.points[12].y = 2187;
		lissajous.points[12].suppressPreviousTrack = false;
		lissajous.points[13].x = 475;
		lissajous.points[13].y = 2322;
		lissajous.points[13].suppressPreviousTrack = false;
		lissajous.points[14].x = 469;
		lissajous.points[14].y = 2488;
		lissajous.points[14].suppressPreviousTrack = false;
		lissajous.points[15].x = 475;
		lissajous.points[15].y = 2635;
		lissajous.points[15].suppressPreviousTrack = false;
		lissajous.points[16].x = 488;
		lissajous.points[16].y = 2789;
		lissajous.points[16].suppressPreviousTrack = false;
		lissajous.points[17].x = 520;
		lissajous.points[17].y = 2917;
		lissajous.points[17].suppressPreviousTrack = false;
		lissajous.points[18].x = 546;
		lissajous.points[18].y = 3038;
		lissajous.points[18].suppressPreviousTrack = false;
		lissajous.points[19].x = 584;
		lissajous.points[19].y = 3141;
		lissajous.points[19].suppressPreviousTrack = false;
		lissajous.points[20].x = 629;
		lissajous.points[20].y = 3237;
		lissajous.points[20].suppressPreviousTrack = false;
		lissajous.points[21].x = 680;
		lissajous.points[21].y = 3333;
		lissajous.points[21].suppressPreviousTrack = false;
		lissajous.points[22].x = 757;
		lissajous.points[22].y = 3442;
		lissajous.points[22].suppressPreviousTrack = false;
		lissajous.points[23].x = 827;
		lissajous.points[23].y = 3538;
		lissajous.points[23].suppressPreviousTrack = false;
		lissajous.points[24].x = 891;
		lissajous.points[24].y = 3602;
		lissajous.points[24].suppressPreviousTrack = false;
		lissajous.points[25].x = 955;
		lissajous.points[25].y = 3672;
		lissajous.points[25].suppressPreviousTrack = false;
		lissajous.points[26].x = 1045;
		lissajous.points[26].y = 3755;
		lissajous.points[26].suppressPreviousTrack = false;
		lissajous.points[27].x = 1154;
		lissajous.points[27].y = 3832;
		lissajous.points[27].suppressPreviousTrack = false;
		lissajous.points[28].x = 1250;
		lissajous.points[28].y = 3890;
		lissajous.points[28].suppressPreviousTrack = false;
		lissajous.points[29].x = 1346;
		lissajous.points[29].y = 3941;
		lissajous.points[29].suppressPreviousTrack = false;
		lissajous.points[30].x = 1448;
		lissajous.points[30].y = 3986;
		lissajous.points[30].suppressPreviousTrack = false;
		lissajous.points[31].x = 1557;
		lissajous.points[31].y = 4024;
		lissajous.points[31].suppressPreviousTrack = false;
		lissajous.points[32].x = 1646;
		lissajous.points[32].y = 4050;
		lissajous.points[32].suppressPreviousTrack = false;
		lissajous.points[33].x = 1736;
		lissajous.points[33].y = 4069;
		lissajous.points[33].suppressPreviousTrack = false;
		lissajous.points[34].x = 1838;
		lissajous.points[34].y = 4082;
		lissajous.points[34].suppressPreviousTrack = false;
		lissajous.points[35].x = 1960;
		lissajous.points[35].y = 4088;
		lissajous.points[35].suppressPreviousTrack = false;
		lissajous.points[36].x = 2056;
		lissajous.points[36].y = 4088;
		lissajous.points[36].suppressPreviousTrack = false;
		lissajous.points[37].x = 2146;
		lissajous.points[37].y = 4088;
		lissajous.points[37].suppressPreviousTrack = false;
		lissajous.points[38].x = 2261;
		lissajous.points[38].y = 4075;
		lissajous.points[38].suppressPreviousTrack = false;
		lissajous.points[39].x = 2370;
		lissajous.points[39].y = 4056;
		lissajous.points[39].suppressPreviousTrack = false;
		lissajous.points[40].x = 2478;
		lissajous.points[40].y = 4024;
		lissajous.points[40].suppressPreviousTrack = false;
		lissajous.points[41].x = 2574;
		lissajous.points[41].y = 3998;
		lissajous.points[41].suppressPreviousTrack = false;
		lissajous.points[42].x = 2670;
		lissajous.points[42].y = 3960;
		lissajous.points[42].suppressPreviousTrack = false;
		lissajous.points[43].x = 2760;
		lissajous.points[43].y = 3922;
		lissajous.points[43].suppressPreviousTrack = false;
		lissajous.points[44].x = 2843;
		lissajous.points[44].y = 3877;
		lissajous.points[44].suppressPreviousTrack = false;
		lissajous.points[45].x = 2952;
		lissajous.points[45].y = 3813;
		lissajous.points[45].suppressPreviousTrack = false;
		lissajous.points[46].x = 3029;
		lissajous.points[46].y = 3755;
		lissajous.points[46].suppressPreviousTrack = false;
		lissajous.points[47].x = 3118;
		lissajous.points[47].y = 3685;
		lissajous.points[47].suppressPreviousTrack = false;
		lissajous.points[48].x = 3195;
		lissajous.points[48].y = 3608;
		lissajous.points[48].suppressPreviousTrack = false;
		lissajous.points[49].x = 3259;
		lissajous.points[49].y = 3525;
		lissajous.points[49].suppressPreviousTrack = false;
		lissajous.points[50].x = 3323;
		lissajous.points[50].y = 3448;
		lissajous.points[50].suppressPreviousTrack = false;
		lissajous.points[51].x = 3387;
		lissajous.points[51].y = 3358;
		lissajous.points[51].suppressPreviousTrack = false;
		lissajous.points[52].x = 3432;
		lissajous.points[52].y = 3262;
		lissajous.points[52].suppressPreviousTrack = false;
		lissajous.points[53].x = 3490;
		lissajous.points[53].y = 3154;
		lissajous.points[53].suppressPreviousTrack = false;
		lissajous.points[54].x = 3522;
		lissajous.points[54].y = 3070;
		lissajous.points[54].suppressPreviousTrack = false;
		lissajous.points[55].x = 3560;
		lissajous.points[55].y = 2981;
		lissajous.points[55].suppressPreviousTrack = false;
		lissajous.points[56].x = 3586;
		lissajous.points[56].y = 2866;
		lissajous.points[56].suppressPreviousTrack = false;
		lissajous.points[57].x = 3605;
		lissajous.points[57].y = 2750;
		lissajous.points[57].suppressPreviousTrack = false;
		lissajous.points[58].x = 3618;
		lissajous.points[58].y = 2616;
		lissajous.points[58].suppressPreviousTrack = false;
		lissajous.points[59].x = 3630;
		lissajous.points[59].y = 2488;
		lissajous.points[59].suppressPreviousTrack = false;
		lissajous.points[60].x = 3630;
		lissajous.points[60].y = 2360;
		lissajous.points[60].suppressPreviousTrack = false;
		lissajous.points[61].x = 3618;
		lissajous.points[61].y = 2251;
		lissajous.points[61].suppressPreviousTrack = false;
		lissajous.points[62].x = 3598;
		lissajous.points[62].y = 2155;
		lissajous.points[62].suppressPreviousTrack = false;
		lissajous.points[63].x = 3573;
		lissajous.points[63].y = 2040;
		lissajous.points[63].suppressPreviousTrack = false;
		lissajous.points[64].x = 3541;
		lissajous.points[64].y = 1944;
		lissajous.points[64].suppressPreviousTrack = false;
		lissajous.points[65].x = 3509;
		lissajous.points[65].y = 1867;
		lissajous.points[65].suppressPreviousTrack = false;
		lissajous.points[66].x = 3464;
		lissajous.points[66].y = 1784;
		lissajous.points[66].suppressPreviousTrack = false;
		lissajous.points[67].x = 3432;
		lissajous.points[67].y = 1714;
		lissajous.points[67].suppressPreviousTrack = false;
		lissajous.points[68].x = 3381;
		lissajous.points[68].y = 1630;
		lissajous.points[68].suppressPreviousTrack = false;
		lissajous.points[69].x = 3349;
		lissajous.points[69].y = 1592;
		lissajous.points[69].suppressPreviousTrack = false;
		lissajous.points[70].x = 3310;
		lissajous.points[70].y = 1541;
		lissajous.points[70].suppressPreviousTrack = false;
		lissajous.points[71].x = 2338;
		lissajous.points[71].y = 549;
		lissajous.points[71].suppressPreviousTrack = false;
		lissajous.points[72].x = 2306;
		lissajous.points[72].y = 523;
		lissajous.points[72].suppressPreviousTrack = false;
		lissajous.points[73].x = 2274;
		lissajous.points[73].y = 491;
		lissajous.points[73].suppressPreviousTrack = false;
		lissajous.points[74].x = 2229;
		lissajous.points[74].y = 472;
		lissajous.points[74].suppressPreviousTrack = false;
		lissajous.points[75].x = 2178;
		lissajous.points[75].y = 446;
		lissajous.points[75].suppressPreviousTrack = false;
		lissajous.points[76].x = 2139;
		lissajous.points[76].y = 434;
		lissajous.points[76].suppressPreviousTrack = false;
		lissajous.points[77].x = 2094;
		lissajous.points[77].y = 434;
		lissajous.points[77].suppressPreviousTrack = false;
		lissajous.points[78].x = 2050;
		lissajous.points[78].y = 434;
		lissajous.points[78].suppressPreviousTrack = false;
		lissajous.points[79].x = 2024;
		lissajous.points[79].y = 427;
		lissajous.points[79].suppressPreviousTrack = false;
		lissajous.points[80].x = 846;
		lissajous.points[80].y = 2091;
		lissajous.points[80].suppressPreviousTrack = true;
		lissajous.points[81].x = 1006;
		lissajous.points[81].y = 2085;
		lissajous.points[81].suppressPreviousTrack = false;
		lissajous.points[82].x = 1250;
		lissajous.points[82].y = 2706;
		lissajous.points[82].suppressPreviousTrack = false;
		lissajous.points[83].x = 1090;
		lissajous.points[83].y = 2725;
		lissajous.points[83].suppressPreviousTrack = false;
		lissajous.points[84].x = 942;
		lissajous.points[84].y = 2290;
		lissajous.points[84].suppressPreviousTrack = false;
		lissajous.points[85].x = 802;
		lissajous.points[85].y = 2725;
		lissajous.points[85].suppressPreviousTrack = false;
		lissajous.points[86].x = 584;
		lissajous.points[86].y = 2725;
		lissajous.points[86].suppressPreviousTrack = false;
		lissajous.points[87].x = 840;
		lissajous.points[87].y = 2098;
		lissajous.points[87].suppressPreviousTrack = false;
		lissajous.points[88].x = 1416;
		lissajous.points[88].y = 2078;
		lissajous.points[88].suppressPreviousTrack = true;
		lissajous.points[89].x = 1410;
		lissajous.points[89].y = 2578;
		lissajous.points[89].suppressPreviousTrack = false;
		lissajous.points[90].x = 1333;
		lissajous.points[90].y = 2590;
		lissajous.points[90].suppressPreviousTrack = false;
		lissajous.points[91].x = 1320;
		lissajous.points[91].y = 2706;
		lissajous.points[91].suppressPreviousTrack = false;
		lissajous.points[92].x = 1582;
		lissajous.points[92].y = 2699;
		lissajous.points[92].suppressPreviousTrack = false;
		lissajous.points[93].x = 1582;
		lissajous.points[93].y = 2085;
		lissajous.points[93].suppressPreviousTrack = false;
		lissajous.points[94].x = 1429;
		lissajous.points[94].y = 2078;
		lissajous.points[94].suppressPreviousTrack = false;
		lissajous.points[95].x = 1890;
		lissajous.points[95].y = 2066;
		lissajous.points[95].suppressPreviousTrack = true;
		lissajous.points[96].x = 1666;
		lissajous.points[96].y = 2712;
		lissajous.points[96].suppressPreviousTrack = false;
		lissajous.points[97].x = 1851;
		lissajous.points[97].y = 2712;
		lissajous.points[97].suppressPreviousTrack = false;
		lissajous.points[98].x = 1992;
		lissajous.points[98].y = 2277;
		lissajous.points[98].suppressPreviousTrack = false;
		lissajous.points[99].x = 2133;
		lissajous.points[99].y = 2712;
		lissajous.points[99].suppressPreviousTrack = false;
		lissajous.points[100].x = 2325;
		lissajous.points[100].y = 2725;
		lissajous.points[100].suppressPreviousTrack = false;
		lissajous.points[101].x = 2069;
		lissajous.points[101].y = 2085;
		lissajous.points[101].suppressPreviousTrack = false;
		lissajous.points[102].x = 1890;
		lissajous.points[102].y = 2091;
		lissajous.points[102].suppressPreviousTrack = false;
		lissajous.points[103].x = 2882;
		lissajous.points[103].y = 2098;
		lissajous.points[103].suppressPreviousTrack = true;
		lissajous.points[104].x = 2811;
		lissajous.points[104].y = 2066;
		lissajous.points[104].suppressPreviousTrack = false;
		lissajous.points[105].x = 2722;
		lissajous.points[105].y = 2046;
		lissajous.points[105].suppressPreviousTrack = false;
		lissajous.points[106].x = 2613;
		lissajous.points[106].y = 2053;
		lissajous.points[106].suppressPreviousTrack = false;
		lissajous.points[107].x = 2530;
		lissajous.points[107].y = 2072;
		lissajous.points[107].suppressPreviousTrack = false;
		lissajous.points[108].x = 2414;
		lissajous.points[108].y = 2149;
		lissajous.points[108].suppressPreviousTrack = false;
		lissajous.points[109].x = 2344;
		lissajous.points[109].y = 2258;
		lissajous.points[109].suppressPreviousTrack = false;
		lissajous.points[110].x = 2325;
		lissajous.points[110].y = 2373;
		lissajous.points[110].suppressPreviousTrack = false;
		lissajous.points[111].x = 2331;
		lissajous.points[111].y = 2482;
		lissajous.points[111].suppressPreviousTrack = false;
		lissajous.points[112].x = 2370;
		lissajous.points[112].y = 2590;
		lissajous.points[112].suppressPreviousTrack = false;
		lissajous.points[113].x = 2427;
		lissajous.points[113].y = 2648;
		lissajous.points[113].suppressPreviousTrack = false;
		lissajous.points[114].x = 2485;
		lissajous.points[114].y = 2686;
		lissajous.points[114].suppressPreviousTrack = false;
		lissajous.points[115].x = 2555;
		lissajous.points[115].y = 2718;
		lissajous.points[115].suppressPreviousTrack = false;
		lissajous.points[116].x = 2613;
		lissajous.points[116].y = 2725;
		lissajous.points[116].suppressPreviousTrack = false;
		lissajous.points[117].x = 2677;
		lissajous.points[117].y = 2731;
		lissajous.points[117].suppressPreviousTrack = false;
		lissajous.points[118].x = 2741;
		lissajous.points[118].y = 2718;
		lissajous.points[118].suppressPreviousTrack = false;
		lissajous.points[119].x = 2805;
		lissajous.points[119].y = 2693;
		lissajous.points[119].suppressPreviousTrack = false;
		lissajous.points[120].x = 2862;
		lissajous.points[120].y = 2648;
		lissajous.points[120].suppressPreviousTrack = false;
		lissajous.points[121].x = 2901;
		lissajous.points[121].y = 2597;
		lissajous.points[121].suppressPreviousTrack = false;
		lissajous.points[122].x = 2926;
		lissajous.points[122].y = 2539;
		lissajous.points[122].suppressPreviousTrack = false;
		lissajous.points[123].x = 2926;
		lissajous.points[123].y = 2482;
		lissajous.points[123].suppressPreviousTrack = false;
		lissajous.points[124].x = 2926;
		lissajous.points[124].y = 2437;
		lissajous.points[124].suppressPreviousTrack = false;
		lissajous.points[125].x = 2933;
		lissajous.points[125].y = 2392;
		lissajous.points[125].suppressPreviousTrack = false;
		lissajous.points[126].x = 2920;
		lissajous.points[126].y = 2341;
		lissajous.points[126].suppressPreviousTrack = false;
		lissajous.points[127].x = 2510;
		lissajous.points[127].y = 2328;
		lissajous.points[127].suppressPreviousTrack = false;
		lissajous.points[128].x = 2536;
		lissajous.points[128].y = 2264;
		lissajous.points[128].suppressPreviousTrack = false;
		lissajous.points[129].x = 2562;
		lissajous.points[129].y = 2245;
		lissajous.points[129].suppressPreviousTrack = false;
		lissajous.points[130].x = 2613;
		lissajous.points[130].y = 2219;
		lissajous.points[130].suppressPreviousTrack = false;
		lissajous.points[131].x = 2664;
		lissajous.points[131].y = 2206;
		lissajous.points[131].suppressPreviousTrack = false;
		lissajous.points[132].x = 2728;
		lissajous.points[132].y = 2213;
		lissajous.points[132].suppressPreviousTrack = false;
		lissajous.points[133].x = 2779;
		lissajous.points[133].y = 2232;
		lissajous.points[133].suppressPreviousTrack = false;
		lissajous.points[134].x = 2818;
		lissajous.points[134].y = 2245;
		lissajous.points[134].suppressPreviousTrack = false;
		lissajous.points[135].x = 2850;
		lissajous.points[135].y = 2258;
		lissajous.points[135].suppressPreviousTrack = false;
		lissajous.points[136].x = 2901;
		lissajous.points[136].y = 2123;
		lissajous.points[136].suppressPreviousTrack = false;
		lissajous.points[137].x = 2510;
		lissajous.points[137].y = 2475;
		lissajous.points[137].suppressPreviousTrack = true;
		lissajous.points[138].x = 2530;
		lissajous.points[138].y = 2526;
		lissajous.points[138].suppressPreviousTrack = false;
		lissajous.points[139].x = 2555;
		lissajous.points[139].y = 2571;
		lissajous.points[139].suppressPreviousTrack = false;
		lissajous.points[140].x = 2594;
		lissajous.points[140].y = 2597;
		lissajous.points[140].suppressPreviousTrack = false;
		lissajous.points[141].x = 2638;
		lissajous.points[141].y = 2597;
		lissajous.points[141].suppressPreviousTrack = false;
		lissajous.points[142].x = 2670;
		lissajous.points[142].y = 2597;
		lissajous.points[142].suppressPreviousTrack = false;
		lissajous.points[143].x = 2702;
		lissajous.points[143].y = 2571;
		lissajous.points[143].suppressPreviousTrack = false;
		lissajous.points[144].x = 2728;
		lissajous.points[144].y = 2546;
		lissajous.points[144].suppressPreviousTrack = false;
		lissajous.points[145].x = 2747;
		lissajous.points[145].y = 2514;
		lissajous.points[145].suppressPreviousTrack = false;
		lissajous.points[146].x = 2754;
		lissajous.points[146].y = 2469;
		lissajous.points[146].suppressPreviousTrack = false;
		lissajous.points[147].x = 2530;
		lissajous.points[147].y = 2469;
		lissajous.points[147].suppressPreviousTrack = false;
		lissajous.points[148].x = 2504;
		lissajous.points[148].y = 2475;
		lissajous.points[148].suppressPreviousTrack = false;
		lissajous.points[149].x = 3003;
		lissajous.points[149].y = 2098;
		lissajous.points[149].suppressPreviousTrack = true;
		lissajous.points[150].x = 3029;
		lissajous.points[150].y = 2213;
		lissajous.points[150].suppressPreviousTrack = false;
		lissajous.points[151].x = 3048;
		lissajous.points[151].y = 2219;
		lissajous.points[151].suppressPreviousTrack = false;
		lissajous.points[152].x = 3086;
		lissajous.points[152].y = 2213;
		lissajous.points[152].suppressPreviousTrack = false;
		lissajous.points[153].x = 3144;
		lissajous.points[153].y = 2200;
		lissajous.points[153].suppressPreviousTrack = false;
		lissajous.points[154].x = 3195;
		lissajous.points[154].y = 2194;
		lissajous.points[154].suppressPreviousTrack = false;
		lissajous.points[155].x = 3253;
		lissajous.points[155].y = 2206;
		lissajous.points[155].suppressPreviousTrack = false;
		lissajous.points[156].x = 3285;
		lissajous.points[156].y = 2219;
		lissajous.points[156].suppressPreviousTrack = false;
		lissajous.points[157].x = 3317;
		lissajous.points[157].y = 2277;
		lissajous.points[157].suppressPreviousTrack = false;
		lissajous.points[158].x = 3298;
		lissajous.points[158].y = 2309;
		lissajous.points[158].suppressPreviousTrack = false;
		lissajous.points[159].x = 3259;
		lissajous.points[159].y = 2322;
		lissajous.points[159].suppressPreviousTrack = false;
		lissajous.points[160].x = 3195;
		lissajous.points[160].y = 2341;
		lissajous.points[160].suppressPreviousTrack = false;
		lissajous.points[161].x = 3106;
		lissajous.points[161].y = 2379;
		lissajous.points[161].suppressPreviousTrack = false;
		lissajous.points[162].x = 3054;
		lissajous.points[162].y = 2411;
		lissajous.points[162].suppressPreviousTrack = false;
		lissajous.points[163].x = 3022;
		lissajous.points[163].y = 2475;
		lissajous.points[163].suppressPreviousTrack = false;
		lissajous.points[164].x = 3022;
		lissajous.points[164].y = 2552;
		lissajous.points[164].suppressPreviousTrack = false;
		lissajous.points[165].x = 3042;
		lissajous.points[165].y = 2616;
		lissajous.points[165].suppressPreviousTrack = false;
		lissajous.points[166].x = 3080;
		lissajous.points[166].y = 2661;
		lissajous.points[166].suppressPreviousTrack = false;
		lissajous.points[167].x = 3131;
		lissajous.points[167].y = 2693;
		lissajous.points[167].suppressPreviousTrack = false;
		lissajous.points[168].x = 3182;
		lissajous.points[168].y = 2706;
		lissajous.points[168].suppressPreviousTrack = false;
		lissajous.points[169].x = 3253;
		lissajous.points[169].y = 2718;
		lissajous.points[169].suppressPreviousTrack = false;
		lissajous.points[170].x = 3304;
		lissajous.points[170].y = 2718;
		lissajous.points[170].suppressPreviousTrack = false;
		lissajous.points[171].x = 3355;
		lissajous.points[171].y = 2712;
		lissajous.points[171].suppressPreviousTrack = false;
		lissajous.points[172].x = 3406;
		lissajous.points[172].y = 2693;
		lissajous.points[172].suppressPreviousTrack = false;
		lissajous.points[173].x = 3451;
		lissajous.points[173].y = 2680;
		lissajous.points[173].suppressPreviousTrack = false;
		lissajous.points[174].x = 3419;
		lissajous.points[174].y = 2578;
		lissajous.points[174].suppressPreviousTrack = false;
		lissajous.points[175].x = 3342;
		lissajous.points[175].y = 2603;
		lissajous.points[175].suppressPreviousTrack = false;
		lissajous.points[176].x = 3291;
		lissajous.points[176].y = 2603;
		lissajous.points[176].suppressPreviousTrack = false;
		lissajous.points[177].x = 3259;
		lissajous.points[177].y = 2603;
		lissajous.points[177].suppressPreviousTrack = false;
		lissajous.points[178].x = 3221;
		lissajous.points[178].y = 2590;
		lissajous.points[178].suppressPreviousTrack = false;
		lissajous.points[179].x = 3195;
		lissajous.points[179].y = 2558;
		lissajous.points[179].suppressPreviousTrack = false;
		lissajous.points[180].x = 3221;
		lissajous.points[180].y = 2520;
		lissajous.points[180].suppressPreviousTrack = false;
		lissajous.points[181].x = 3240;
		lissajous.points[181].y = 2501;
		lissajous.points[181].suppressPreviousTrack = false;
		lissajous.points[182].x = 3291;
		lissajous.points[182].y = 2488;
		lissajous.points[182].suppressPreviousTrack = false;
		lissajous.points[183].x = 3349;
		lissajous.points[183].y = 2469;
		lissajous.points[183].suppressPreviousTrack = false;
		lissajous.points[184].x = 3394;
		lissajous.points[184].y = 2450;
		lissajous.points[184].suppressPreviousTrack = false;
		lissajous.points[185].x = 3451;
		lissajous.points[185].y = 2405;
		lissajous.points[185].suppressPreviousTrack = false;
		lissajous.points[186].x = 3477;
		lissajous.points[186].y = 2354;
		lissajous.points[186].suppressPreviousTrack = false;
		lissajous.points[187].x = 3490;
		lissajous.points[187].y = 2296;
		lissajous.points[187].suppressPreviousTrack = false;
		lissajous.points[188].x = 3477;
		lissajous.points[188].y = 2226;
		lissajous.points[188].suppressPreviousTrack = false;
		lissajous.points[189].x = 3458;
		lissajous.points[189].y = 2181;
		lissajous.points[189].suppressPreviousTrack = false;
		lissajous.points[190].x = 3432;
		lissajous.points[190].y = 2149;
		lissajous.points[190].suppressPreviousTrack = false;
		lissajous.points[191].x = 3387;
		lissajous.points[191].y = 2104;
		lissajous.points[191].suppressPreviousTrack = false;
		lissajous.points[192].x = 3317;
		lissajous.points[192].y = 2072;
		lissajous.points[192].suppressPreviousTrack = false;
		lissajous.points[193].x = 3253;
		lissajous.points[193].y = 2066;
		lissajous.points[193].suppressPreviousTrack = false;
		lissajous.points[194].x = 3163;
		lissajous.points[194].y = 2059;
		lissajous.points[194].suppressPreviousTrack = false;
		lissajous.points[195].x = 3118;
		lissajous.points[195].y = 2066;
		lissajous.points[195].suppressPreviousTrack = false;
		lissajous.points[196].x = 3074;
		lissajous.points[196].y = 2078;
		lissajous.points[196].suppressPreviousTrack = false;
		lissajous.points[197].x = 3029;
		lissajous.points[197].y = 2085;
		lissajous.points[197].suppressPreviousTrack = false;
		lissajous.points[198].x = 3010;
		lissajous.points[198].y = 2098;
		lissajous.points[198].suppressPreviousTrack = false;
		lissajous.points[199].x = 1486;
		lissajous.points[199].y = 2821;
		lissajous.points[199].suppressPreviousTrack = true;
		lissajous.points[200].x = 1461;
		lissajous.points[200].y = 2821;
		lissajous.points[200].suppressPreviousTrack = false;
		lissajous.points[201].x = 1429;
		lissajous.points[201].y = 2840;
		lissajous.points[201].suppressPreviousTrack = false;
		lissajous.points[202].x = 1403;
		lissajous.points[202].y = 2859;
		lissajous.points[202].suppressPreviousTrack = false;
		lissajous.points[203].x = 1378;
		lissajous.points[203].y = 2904;
		lissajous.points[203].suppressPreviousTrack = false;
		lissajous.points[204].x = 1378;
		lissajous.points[204].y = 2955;
		lissajous.points[204].suppressPreviousTrack = false;
		lissajous.points[205].x = 1390;
		lissajous.points[205].y = 2994;
		lissajous.points[205].suppressPreviousTrack = false;
		lissajous.points[206].x = 1435;
		lissajous.points[206].y = 3019;
		lissajous.points[206].suppressPreviousTrack = false;
		lissajous.points[207].x = 1467;
		lissajous.points[207].y = 3032;
		lissajous.points[207].suppressPreviousTrack = false;
		lissajous.points[208].x = 1525;
		lissajous.points[208].y = 3032;
		lissajous.points[208].suppressPreviousTrack = false;
		lissajous.points[209].x = 1563;
		lissajous.points[209].y = 3013;
		lissajous.points[209].suppressPreviousTrack = false;
		lissajous.points[210].x = 1589;
		lissajous.points[210].y = 2981;
		lissajous.points[210].suppressPreviousTrack = false;
		lissajous.points[211].x = 1595;
		lissajous.points[211].y = 2949;
		lissajous.points[211].suppressPreviousTrack = false;
		lissajous.points[212].x = 1595;
		lissajous.points[212].y = 2898;
		lissajous.points[212].suppressPreviousTrack = false;
		lissajous.points[213].x = 1570;
		lissajous.points[213].y = 2866;
		lissajous.points[213].suppressPreviousTrack = false;
		lissajous.points[214].x = 1538;
		lissajous.points[214].y = 2840;
		lissajous.points[214].suppressPreviousTrack = false;
		lissajous.points[215].x = 1512;
		lissajous.points[215].y = 2827;
		lissajous.points[215].suppressPreviousTrack = false;
		lissajous.points[216].x = 1480;
		lissajous.points[216].y = 2827;
		lissajous.points[216].suppressPreviousTrack = false;
		
		lissajous.length = 217;
	}
	#endif

	#if defined(KERSTBOOM)
	{
		lissajous.points[0].x = 1843;
		lissajous.points[0].y = 421;
		lissajous.points[0].suppressPreviousTrack = true;
		lissajous.points[1].x = 1907;
		lissajous.points[1].y = 1003;
		lissajous.points[1].suppressPreviousTrack = false;
		lissajous.points[2].x = 1818;
		lissajous.points[2].y = 997;
		lissajous.points[2].suppressPreviousTrack = false;
		lissajous.points[3].x = 1690;
		lissajous.points[3].y = 965;
		lissajous.points[3].suppressPreviousTrack = false;
		lissajous.points[4].x = 1542;
		lissajous.points[4].y = 965;
		lissajous.points[4].suppressPreviousTrack = false;
		lissajous.points[5].x = 1427;
		lissajous.points[5].y = 952;
		lissajous.points[5].suppressPreviousTrack = false;
		lissajous.points[6].x = 1325;
		lissajous.points[6].y = 958;
		lissajous.points[6].suppressPreviousTrack = false;
		lissajous.points[7].x = 1171;
		lissajous.points[7].y = 971;
		lissajous.points[7].suppressPreviousTrack = false;
		lissajous.points[8].x = 1037;
		lissajous.points[8].y = 984;
		lissajous.points[8].suppressPreviousTrack = false;
		lissajous.points[9].x = 1005;
		lissajous.points[9].y = 1003;
		lissajous.points[9].suppressPreviousTrack = false;
		lissajous.points[10].x = 986;
		lissajous.points[10].y = 1048;
		lissajous.points[10].suppressPreviousTrack = false;
		lissajous.points[11].x = 1056;
		lissajous.points[11].y = 1112;
		lissajous.points[11].suppressPreviousTrack = false;
		lissajous.points[12].x = 1190;
		lissajous.points[12].y = 1246;
		lissajous.points[12].suppressPreviousTrack = false;
		lissajous.points[13].x = 1344;
		lissajous.points[13].y = 1419;
		lissajous.points[13].suppressPreviousTrack = false;
		lissajous.points[14].x = 1485;
		lissajous.points[14].y = 1598;
		lissajous.points[14].suppressPreviousTrack = false;
		lissajous.points[15].x = 1594;
		lissajous.points[15].y = 1765;
		lissajous.points[15].suppressPreviousTrack = false;
		lissajous.points[16].x = 1658;
		lissajous.points[16].y = 1867;
		lissajous.points[16].suppressPreviousTrack = false;
		lissajous.points[17].x = 1517;
		lissajous.points[17].y = 1867;
		lissajous.points[17].suppressPreviousTrack = false;
		lissajous.points[18].x = 1478;
		lissajous.points[18].y = 1880;
		lissajous.points[18].suppressPreviousTrack = false;
		lissajous.points[19].x = 1459;
		lissajous.points[19].y = 1912;
		lissajous.points[19].suppressPreviousTrack = false;
		lissajous.points[20].x = 1472;
		lissajous.points[20].y = 1938;
		lissajous.points[20].suppressPreviousTrack = false;
		lissajous.points[21].x = 1555;
		lissajous.points[21].y = 2014;
		lissajous.points[21].suppressPreviousTrack = false;
		lissajous.points[22].x = 1670;
		lissajous.points[22].y = 2168;
		lissajous.points[22].suppressPreviousTrack = false;
		lissajous.points[23].x = 1766;
		lissajous.points[23].y = 2334;
		lissajous.points[23].suppressPreviousTrack = false;
		lissajous.points[24].x = 1824;
		lissajous.points[24].y = 2456;
		lissajous.points[24].suppressPreviousTrack = false;
		lissajous.points[25].x = 1850;
		lissajous.points[25].y = 2507;
		lissajous.points[25].suppressPreviousTrack = false;
		lissajous.points[26].x = 1773;
		lissajous.points[26].y = 2507;
		lissajous.points[26].suppressPreviousTrack = false;
		lissajous.points[27].x = 1747;
		lissajous.points[27].y = 2520;
		lissajous.points[27].suppressPreviousTrack = false;
		lissajous.points[28].x = 1728;
		lissajous.points[28].y = 2552;
		lissajous.points[28].suppressPreviousTrack = false;
		lissajous.points[29].x = 1734;
		lissajous.points[29].y = 2578;
		lissajous.points[29].suppressPreviousTrack = false;
		lissajous.points[30].x = 1786;
		lissajous.points[30].y = 2661;
		lissajous.points[30].suppressPreviousTrack = false;
		lissajous.points[31].x = 1856;
		lissajous.points[31].y = 2789;
		lissajous.points[31].suppressPreviousTrack = false;
		lissajous.points[32].x = 1920;
		lissajous.points[32].y = 2904;
		lissajous.points[32].suppressPreviousTrack = false;
		lissajous.points[33].x = 2054;
		lissajous.points[33].y = 3243;
		lissajous.points[33].suppressPreviousTrack = false;
		lissajous.points[34].x = 2138;
		lissajous.points[34].y = 3000;
		lissajous.points[34].suppressPreviousTrack = false;
		lissajous.points[35].x = 2208;
		lissajous.points[35].y = 2840;
		lissajous.points[35].suppressPreviousTrack = false;
		lissajous.points[36].x = 2342;
		lissajous.points[36].y = 2603;
		lissajous.points[36].suppressPreviousTrack = false;
		lissajous.points[37].x = 2362;
		lissajous.points[37].y = 2546;
		lissajous.points[37].suppressPreviousTrack = false;
		lissajous.points[38].x = 2349;
		lissajous.points[38].y = 2526;
		lissajous.points[38].suppressPreviousTrack = false;
		lissajous.points[39].x = 2330;
		lissajous.points[39].y = 2501;
		lissajous.points[39].suppressPreviousTrack = false;
		lissajous.points[40].x = 2240;
		lissajous.points[40].y = 2507;
		lissajous.points[40].suppressPreviousTrack = false;
		lissajous.points[41].x = 2304;
		lissajous.points[41].y = 2366;
		lissajous.points[41].suppressPreviousTrack = false;
		lissajous.points[42].x = 2387;
		lissajous.points[42].y = 2226;
		lissajous.points[42].suppressPreviousTrack = false;
		lissajous.points[43].x = 2483;
		lissajous.points[43].y = 2098;
		lissajous.points[43].suppressPreviousTrack = false;
		lissajous.points[44].x = 2618;
		lissajous.points[44].y = 1931;
		lissajous.points[44].suppressPreviousTrack = false;
		lissajous.points[45].x = 2630;
		lissajous.points[45].y = 1893;
		lissajous.points[45].suppressPreviousTrack = false;
		lissajous.points[46].x = 2624;
		lissajous.points[46].y = 1880;
		lissajous.points[46].suppressPreviousTrack = false;
		lissajous.points[47].x = 2598;
		lissajous.points[47].y = 1854;
		lissajous.points[47].suppressPreviousTrack = false;
		lissajous.points[48].x = 2560;
		lissajous.points[48].y = 1854;
		lissajous.points[48].suppressPreviousTrack = false;
		lissajous.points[49].x = 2445;
		lissajous.points[49].y = 1861;
		lissajous.points[49].suppressPreviousTrack = false;
		lissajous.points[50].x = 2541;
		lissajous.points[50].y = 1707;
		lissajous.points[50].suppressPreviousTrack = false;
		lissajous.points[51].x = 2694;
		lissajous.points[51].y = 1483;
		lissajous.points[51].suppressPreviousTrack = false;
		lissajous.points[52].x = 2797;
		lissajous.points[52].y = 1374;
		lissajous.points[52].suppressPreviousTrack = false;
		lissajous.points[53].x = 2906;
		lissajous.points[53].y = 1253;
		lissajous.points[53].suppressPreviousTrack = false;
		lissajous.points[54].x = 3014;
		lissajous.points[54].y = 1144;
		lissajous.points[54].suppressPreviousTrack = false;
		lissajous.points[55].x = 3098;
		lissajous.points[55].y = 1061;
		lissajous.points[55].suppressPreviousTrack = false;
		lissajous.points[56].x = 3104;
		lissajous.points[56].y = 1016;
		lissajous.points[56].suppressPreviousTrack = false;
		lissajous.points[57].x = 3085;
		lissajous.points[57].y = 984;
		lissajous.points[57].suppressPreviousTrack = false;
		lissajous.points[58].x = 3034;
		lissajous.points[58].y = 984;
		lissajous.points[58].suppressPreviousTrack = false;
		lissajous.points[59].x = 2803;
		lissajous.points[59].y = 1022;
		lissajous.points[59].suppressPreviousTrack = false;
		lissajous.points[60].x = 2611;
		lissajous.points[60].y = 1054;
		lissajous.points[60].suppressPreviousTrack = false;
		lissajous.points[61].x = 2400;
		lissajous.points[61].y = 1061;
		lissajous.points[61].suppressPreviousTrack = false;
		lissajous.points[62].x = 2189;
		lissajous.points[62].y = 1048;
		lissajous.points[62].suppressPreviousTrack = false;
		lissajous.points[63].x = 2176;
		lissajous.points[63].y = 1048;
		lissajous.points[63].suppressPreviousTrack = false;
		lissajous.points[64].x = 2259;
		lissajous.points[64].y = 414;
		lissajous.points[64].suppressPreviousTrack = false;
		lissajous.points[65].x = 2035;
		lissajous.points[65].y = 3352;
		lissajous.points[65].suppressPreviousTrack = true;
		lissajous.points[66].x = 1914;
		lissajous.points[66].y = 3269;
		lissajous.points[66].suppressPreviousTrack = false;
		lissajous.points[67].x = 1958;
		lissajous.points[67].y = 3422;
		lissajous.points[67].suppressPreviousTrack = false;
		lissajous.points[68].x = 1830;
		lissajous.points[68].y = 3525;
		lissajous.points[68].suppressPreviousTrack = false;
		lissajous.points[69].x = 1990;
		lissajous.points[69].y = 3525;
		lissajous.points[69].suppressPreviousTrack = false;
		lissajous.points[70].x = 2048;
		lissajous.points[70].y = 3678;
		lissajous.points[70].suppressPreviousTrack = false;
		lissajous.points[71].x = 2099;
		lissajous.points[71].y = 3518;
		lissajous.points[71].suppressPreviousTrack = false;
		lissajous.points[72].x = 2266;
		lissajous.points[72].y = 3512;
		lissajous.points[72].suppressPreviousTrack = false;
		lissajous.points[73].x = 2131;
		lissajous.points[73].y = 3403;
		lissajous.points[73].suppressPreviousTrack = false;
		lissajous.points[74].x = 2189;
		lissajous.points[74].y = 3262;
		lissajous.points[74].suppressPreviousTrack = false;
		lissajous.points[75].x = 2048;
		lissajous.points[75].y = 3346;
		lissajous.points[75].suppressPreviousTrack = false;
		lissajous.points[76].x = 2035;
		lissajous.points[76].y = 3365;
		lissajous.points[76].suppressPreviousTrack = false;
		lissajous.points[77].x = 1958;
		lissajous.points[77].y = 2200;
		lissajous.points[77].suppressPreviousTrack = true;
		lissajous.points[78].x = 1984;
		lissajous.points[78].y = 2162;
		lissajous.points[78].suppressPreviousTrack = false;
		lissajous.points[79].x = 2022;
		lissajous.points[79].y = 2162;
		lissajous.points[79].suppressPreviousTrack = false;
		lissajous.points[80].x = 1984;
		lissajous.points[80].y = 2130;
		lissajous.points[80].suppressPreviousTrack = false;
		lissajous.points[81].x = 1997;
		lissajous.points[81].y = 2091;
		lissajous.points[81].suppressPreviousTrack = false;
		lissajous.points[82].x = 1971;
		lissajous.points[82].y = 2117;
		lissajous.points[82].suppressPreviousTrack = false;
		lissajous.points[83].x = 1926;
		lissajous.points[83].y = 2085;
		lissajous.points[83].suppressPreviousTrack = false;
		lissajous.points[84].x = 1946;
		lissajous.points[84].y = 2136;
		lissajous.points[84].suppressPreviousTrack = false;
		lissajous.points[85].x = 1907;
		lissajous.points[85].y = 2155;
		lissajous.points[85].suppressPreviousTrack = false;
		lissajous.points[86].x = 1946;
		lissajous.points[86].y = 2168;
		lissajous.points[86].suppressPreviousTrack = false;
		lissajous.points[87].x = 1747;
		lissajous.points[87].y = 1605;
		lissajous.points[87].suppressPreviousTrack = true;
		lissajous.points[88].x = 1779;
		lissajous.points[88].y = 1547;
		lissajous.points[88].suppressPreviousTrack = false;
		lissajous.points[89].x = 1837;
		lissajous.points[89].y = 1547;
		lissajous.points[89].suppressPreviousTrack = false;
		lissajous.points[90].x = 1786;
		lissajous.points[90].y = 1483;
		lissajous.points[90].suppressPreviousTrack = false;
		lissajous.points[91].x = 1811;
		lissajous.points[91].y = 1426;
		lissajous.points[91].suppressPreviousTrack = false;
		lissajous.points[92].x = 1747;
		lissajous.points[92].y = 1464;
		lissajous.points[92].suppressPreviousTrack = false;
		lissajous.points[93].x = 1696;
		lissajous.points[93].y = 1426;
		lissajous.points[93].suppressPreviousTrack = false;
		lissajous.points[94].x = 1709;
		lissajous.points[94].y = 1496;
		lissajous.points[94].suppressPreviousTrack = false;
		lissajous.points[95].x = 1651;
		lissajous.points[95].y = 1541;
		lissajous.points[95].suppressPreviousTrack = false;
		lissajous.points[96].x = 1728;
		lissajous.points[96].y = 1554;
		lissajous.points[96].suppressPreviousTrack = false;
		lissajous.points[97].x = 2483;
		lissajous.points[97].y = 1304;
		lissajous.points[97].suppressPreviousTrack = true;
		lissajous.points[98].x = 2515;
		lissajous.points[98].y = 1317;
		lissajous.points[98].suppressPreviousTrack = false;
		lissajous.points[99].x = 2528;
		lissajous.points[99].y = 1355;
		lissajous.points[99].suppressPreviousTrack = false;
		lissajous.points[100].x = 2554;
		lissajous.points[100].y = 1317;
		lissajous.points[100].suppressPreviousTrack = false;
		lissajous.points[101].x = 2592;
		lissajous.points[101].y = 1310;
		lissajous.points[101].suppressPreviousTrack = false;
		lissajous.points[102].x = 2560;
		lissajous.points[102].y = 1278;
		lissajous.points[102].suppressPreviousTrack = false;
		lissajous.points[103].x = 2573;
		lissajous.points[103].y = 1240;
		lissajous.points[103].suppressPreviousTrack = false;
		lissajous.points[104].x = 2534;
		lissajous.points[104].y = 1259;
		lissajous.points[104].suppressPreviousTrack = false;
		lissajous.points[105].x = 2496;
		lissajous.points[105].y = 1221;
		lissajous.points[105].suppressPreviousTrack = false;
		lissajous.points[106].x = 2496;
		lissajous.points[106].y = 1278;
		lissajous.points[106].suppressPreviousTrack = false;

		lissajous.length = 107;
	}
	#endif
	
	while (1)
	{	
		// Teken de volledige figuur...
		DrawLissajous(&lissajous, 0, lissajous.length);		
	}
}

// Afstand tussen twee punten berekenen met Pythagoras en dan interpoleren...
void DrawLissajous(Lissajous* lissajous, uint16_t startIndex, uint16_t count)
{
	uint16_t i, j;
	
	// Alle punten overlopen.
	for(i = startIndex; i < (startIndex + count - 1); i++)
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
		else
		{
			// Track onderdrukken.
			// Direct naar volgende punt gaan (zonder te interpoleren).
			SetDacX(lissajous->points[i+1].x);
			SetDacY(lissajous->points[i+1].y);
		}
	}
}

//void Delay(void)
//{
//	for(count = 0; count < 100; count++)
//		__NOP();
//}

// Handler die iedere 1ms afloopt. Ingesteld met SystemCoreClockUpdate() en SysTick_Config().
void SysTick_Handler(void)
{
	ticks++;
}

void WaitForMs(uint32_t timespan)
{
	uint32_t startTime = ticks;
	
	while(ticks < startTime + timespan);
}

void SystemClock_Config(void)
{
	RCC->CR |= RCC_CR_HSITRIM_4;														// HSITRIM op 16 zetten, dit is standaard (ook na reset).
	RCC->CR  |= RCC_CR_HSION;																// Internal high speed oscillator enable (8MHz)
	while((RCC->CR & RCC_CR_HSIRDY) == 0);									// Wacht tot HSI zeker ingeschakeld is
	
	RCC->CFGR &= ~RCC_CFGR_SW;															// System clock op HSI zetten (SWS is status geupdatet door hardware)	
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);	// Wachten to effectief HSI in actie is getreden
	
	RCC->CR &= ~RCC_CR_PLLON;																// Eerst PLL uitschakelen
	while((RCC->CR & RCC_CR_PLLRDY) != 0);									// Wacht tot PLL zeker uitgeschakeld is
	
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;								// 01: HSI/PREDIV selected as PLL input clock
	RCC->CFGR2 |= RCC_CFGR2_PREDIV_DIV2;										// prediv = /2		=> 4MHz
	RCC->CFGR |= RCC_CFGR_PLLMUL12;													// PLL multiplied by 12 => 48MHz
	
	FLASH->ACR |= FLASH_ACR_LATENCY;												//  meer dan 24 MHz, dus latency op 1 (p 67)
	
	RCC->CR |= RCC_CR_PLLON;																// PLL inschakelen
	while((RCC->CR & RCC_CR_PLLRDY) == 0);									// Wacht tot PLL zeker ingeschakeld is

	RCC->CFGR |= RCC_CFGR_SW_PLL; 													// PLLCLK selecteren als SYSCLK (48MHz)
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	// Wait until the PLL is switched on
		
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;												// SYSCLK niet meer delen, dus HCLK = 48MHz
	RCC->CFGR |= RCC_CFGR_PPRE_DIV1;												// HCLK niet meer delen, dus PCLK = 48MHz	
	
	SystemCoreClockUpdate();																// Nieuwe waarde van de core frequentie opslaan in SystemCoreClock variabele
	SysTick_Config(48000);																	// Interrupt genereren. Zie core_cm0.h, om na ieder 1ms een interrupt 
																													// te hebben op SysTick_Handler()
}
