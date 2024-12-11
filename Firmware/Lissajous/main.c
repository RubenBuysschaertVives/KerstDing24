// Defines.
//#define MEASURE_LOOP_TIME
// Kies een afbeelding.
#define KERSTBOOM
//#define VIVES
//#define RECTANGLE

// Header files toevoegen.
#include "stm32f091xc.h"
#include "stdio.h"
#include "stdbool.h"
#include "usart2.h"
#include "dac.h"
#include "lissajous.h"

// Functie prototypes aanmaken.
void SystemClock_Config(void);
void WaitForMs(uint32_t timespan);
void DrawLissajous(Lissajous* lissajous, uint16_t count);

// Globale variabelen.
static uint16_t i = 0;
static volatile uint32_t ticks = 0;
#ifdef MEASURE_LOOP_TIME
	static uint32_t startTicks = 0, deltaTicks = 0;
#endif
static char text[101];
static Lissajous lissajous;

// Entry point.
int main(void)
{
	// Initialisaties.
	SystemClock_Config();
	InitUsart2(115200);
	InitDAC();
	
	// Berichtje op de UART (optioneel).
	sprintf(text, "KerstDing24 - Lissajous figuren via DAC's op een Nucleo-F091RC.\r\n");
	StringToUsart2(text);
	
	// Analoge spanningen op nul volt zetten.
	SetDacX(0);
	SetDacY(0);
	
	// Data initialiseren op nul (optioneel).
	for(i = 0; i < MAX_NUMBER_OF_POINTS; i++)
	{
		lissajous.points[i].x = 0;
		lissajous.points[i].y = 0;
		lissajous.points[i].suppressPreviousTrack = false;
	}

	// Data opvullen.
	#ifdef KERSTBOOM
	{
		lissajous.points[0].x = 1850;
		lissajous.points[0].y = 421;
		lissajous.points[0].suppressPreviousTrack = false;

		lissajous.points[1].x = 1914;
		lissajous.points[1].y = 1010;
		lissajous.points[1].suppressPreviousTrack = false;

		lissajous.points[2].x = 1843;
		lissajous.points[2].y = 1010;
		lissajous.points[2].suppressPreviousTrack = false;

		lissajous.points[3].x = 1766;
		lissajous.points[3].y = 1003;
		lissajous.points[3].suppressPreviousTrack = false;

		lissajous.points[4].x = 1677;
		lissajous.points[4].y = 990;
		lissajous.points[4].suppressPreviousTrack = false;

		lissajous.points[5].x = 1600;
		lissajous.points[5].y = 978;
		lissajous.points[5].suppressPreviousTrack = false;

		lissajous.points[6].x = 1510;
		lissajous.points[6].y = 971;
		lissajous.points[6].suppressPreviousTrack = false;

		lissajous.points[7].x = 1376;
		lissajous.points[7].y = 971;
		lissajous.points[7].suppressPreviousTrack = false;

		lissajous.points[8].x = 1318;
		lissajous.points[8].y = 965;
		lissajous.points[8].suppressPreviousTrack = false;

		lissajous.points[9].x = 1222;
		lissajous.points[9].y = 971;
		lissajous.points[9].suppressPreviousTrack = false;

		lissajous.points[10].x = 1171;
		lissajous.points[10].y = 978;
		lissajous.points[10].suppressPreviousTrack = false;

		lissajous.points[11].x = 1094;
		lissajous.points[11].y = 984;
		lissajous.points[11].suppressPreviousTrack = false;

		lissajous.points[12].x = 1018;
		lissajous.points[12].y = 997;
		lissajous.points[12].suppressPreviousTrack = false;

		lissajous.points[13].x = 998;
		lissajous.points[13].y = 1016;
		lissajous.points[13].suppressPreviousTrack = false;

		lissajous.points[14].x = 998;
		lissajous.points[14].y = 1054;
		lissajous.points[14].suppressPreviousTrack = false;

		lissajous.points[15].x = 1005;
		lissajous.points[15].y = 1086;
		lissajous.points[15].suppressPreviousTrack = false;

		lissajous.points[16].x = 1050;
		lissajous.points[16].y = 1112;
		lissajous.points[16].suppressPreviousTrack = false;

		lissajous.points[17].x = 1146;
		lissajous.points[17].y = 1195;
		lissajous.points[17].suppressPreviousTrack = false;

		lissajous.points[18].x = 1210;
		lissajous.points[18].y = 1291;
		lissajous.points[18].suppressPreviousTrack = false;

		lissajous.points[19].x = 1267;
		lissajous.points[19].y = 1336;
		lissajous.points[19].suppressPreviousTrack = false;

		lissajous.points[20].x = 1344;
		lissajous.points[20].y = 1419;
		lissajous.points[20].suppressPreviousTrack = false;

		lissajous.points[21].x = 1402;
		lissajous.points[21].y = 1502;
		lissajous.points[21].suppressPreviousTrack = false;

		lissajous.points[22].x = 1459;
		lissajous.points[22].y = 1573;
		lissajous.points[22].suppressPreviousTrack = false;

		lissajous.points[23].x = 1510;
		lissajous.points[23].y = 1643;
		lissajous.points[23].suppressPreviousTrack = false;

		lissajous.points[24].x = 1581;
		lissajous.points[24].y = 1733;
		lissajous.points[24].suppressPreviousTrack = false;

		lissajous.points[25].x = 1613;
		lissajous.points[25].y = 1790;
		lissajous.points[25].suppressPreviousTrack = false;

		lissajous.points[26].x = 1658;
		lissajous.points[26].y = 1842;
		lissajous.points[26].suppressPreviousTrack = false;

		lissajous.points[27].x = 1670;
		lissajous.points[27].y = 1880;
		lissajous.points[27].suppressPreviousTrack = false;

		lissajous.points[28].x = 1638;
		lissajous.points[28].y = 1880;
		lissajous.points[28].suppressPreviousTrack = false;

		lissajous.points[29].x = 1587;
		lissajous.points[29].y = 1880;
		lissajous.points[29].suppressPreviousTrack = false;

		lissajous.points[30].x = 1523;
		lissajous.points[30].y = 1880;
		lissajous.points[30].suppressPreviousTrack = false;

		lissajous.points[31].x = 1472;
		lissajous.points[31].y = 1874;
		lissajous.points[31].suppressPreviousTrack = false;

		lissajous.points[32].x = 1466;
		lissajous.points[32].y = 1893;
		lissajous.points[32].suppressPreviousTrack = false;

		lissajous.points[33].x = 1466;
		lissajous.points[33].y = 1925;
		lissajous.points[33].suppressPreviousTrack = false;

		lissajous.points[34].x = 1498;
		lissajous.points[34].y = 1963;
		lissajous.points[34].suppressPreviousTrack = false;

		lissajous.points[35].x = 1542;
		lissajous.points[35].y = 2014;
		lissajous.points[35].suppressPreviousTrack = false;

		lissajous.points[36].x = 1613;
		lissajous.points[36].y = 2091;
		lissajous.points[36].suppressPreviousTrack = false;

		lissajous.points[37].x = 1664;
		lissajous.points[37].y = 2162;
		lissajous.points[37].suppressPreviousTrack = false;

		lissajous.points[38].x = 1734;
		lissajous.points[38].y = 2270;
		lissajous.points[38].suppressPreviousTrack = false;

		lissajous.points[39].x = 1792;
		lissajous.points[39].y = 2360;
		lissajous.points[39].suppressPreviousTrack = false;

		lissajous.points[40].x = 1811;
		lissajous.points[40].y = 2405;
		lissajous.points[40].suppressPreviousTrack = false;

		lissajous.points[41].x = 1830;
		lissajous.points[41].y = 2456;
		lissajous.points[41].suppressPreviousTrack = false;

		lissajous.points[42].x = 1856;
		lissajous.points[42].y = 2520;
		lissajous.points[42].suppressPreviousTrack = false;

		lissajous.points[43].x = 1843;
		lissajous.points[43].y = 2526;
		lissajous.points[43].suppressPreviousTrack = false;

		lissajous.points[44].x = 1811;
		lissajous.points[44].y = 2526;
		lissajous.points[44].suppressPreviousTrack = false;

		lissajous.points[45].x = 1766;
		lissajous.points[45].y = 2526;
		lissajous.points[45].suppressPreviousTrack = false;

		lissajous.points[46].x = 1734;
		lissajous.points[46].y = 2526;
		lissajous.points[46].suppressPreviousTrack = false;

		lissajous.points[47].x = 1728;
		lissajous.points[47].y = 2546;
		lissajous.points[47].suppressPreviousTrack = false;

		lissajous.points[48].x = 1734;
		lissajous.points[48].y = 2590;
		lissajous.points[48].suppressPreviousTrack = false;

		lissajous.points[49].x = 1766;
		lissajous.points[49].y = 2642;
		lissajous.points[49].suppressPreviousTrack = false;

		lissajous.points[50].x = 1811;
		lissajous.points[50].y = 2706;
		lissajous.points[50].suppressPreviousTrack = false;

		lissajous.points[51].x = 1856;
		lissajous.points[51].y = 2789;
		lissajous.points[51].suppressPreviousTrack = false;

		lissajous.points[52].x = 1875;
		lissajous.points[52].y = 2821;
		lissajous.points[52].suppressPreviousTrack = false;

		lissajous.points[53].x = 1920;
		lissajous.points[53].y = 2923;
		lissajous.points[53].suppressPreviousTrack = false;

		lissajous.points[54].x = 1978;
		lissajous.points[54].y = 3058;
		lissajous.points[54].suppressPreviousTrack = false;

		lissajous.points[55].x = 2048;
		lissajous.points[55].y = 3243;
		lissajous.points[55].suppressPreviousTrack = false;

		lissajous.points[56].x = 2054;
		lissajous.points[56].y = 3346;
		lissajous.points[56].suppressPreviousTrack = true;

		lissajous.points[57].x = 1926;
		lissajous.points[57].y = 3256;
		lissajous.points[57].suppressPreviousTrack = false;

		lissajous.points[58].x = 1965;
		lissajous.points[58].y = 3429;
		lissajous.points[58].suppressPreviousTrack = false;

		lissajous.points[59].x = 1837;
		lissajous.points[59].y = 3512;
		lissajous.points[59].suppressPreviousTrack = false;

		lissajous.points[60].x = 1990;
		lissajous.points[60].y = 3525;
		lissajous.points[60].suppressPreviousTrack = false;

		lissajous.points[61].x = 2048;
		lissajous.points[61].y = 3678;
		lissajous.points[61].suppressPreviousTrack = false;

		lissajous.points[62].x = 2106;
		lissajous.points[62].y = 3512;
		lissajous.points[62].suppressPreviousTrack = false;

		lissajous.points[63].x = 2266;
		lissajous.points[63].y = 3512;
		lissajous.points[63].suppressPreviousTrack = false;

		lissajous.points[64].x = 2138;
		lissajous.points[64].y = 3410;
		lissajous.points[64].suppressPreviousTrack = false;

		lissajous.points[65].x = 2182;
		lissajous.points[65].y = 3250;
		lissajous.points[65].suppressPreviousTrack = false;

		lissajous.points[66].x = 2054;
		lissajous.points[66].y = 3339;
		lissajous.points[66].suppressPreviousTrack = false;

		lissajous.points[67].x = 2054;
		lissajous.points[67].y = 3243;
		lissajous.points[67].suppressPreviousTrack = true;

		lissajous.points[68].x = 2067;
		lissajous.points[68].y = 3179;
		lissajous.points[68].suppressPreviousTrack = false;

		lissajous.points[69].x = 2112;
		lissajous.points[69].y = 3070;
		lissajous.points[69].suppressPreviousTrack = false;

		lissajous.points[70].x = 2150;
		lissajous.points[70].y = 2962;
		lissajous.points[70].suppressPreviousTrack = false;

		lissajous.points[71].x = 2202;
		lissajous.points[71].y = 2846;
		lissajous.points[71].suppressPreviousTrack = false;

		lissajous.points[72].x = 2259;
		lissajous.points[72].y = 2731;
		lissajous.points[72].suppressPreviousTrack = false;

		lissajous.points[73].x = 2310;
		lissajous.points[73].y = 2629;
		lissajous.points[73].suppressPreviousTrack = false;

		lissajous.points[74].x = 2355;
		lissajous.points[74].y = 2565;
		lissajous.points[74].suppressPreviousTrack = false;

		lissajous.points[75].x = 2362;
		lissajous.points[75].y = 2546;
		lissajous.points[75].suppressPreviousTrack = false;

		lissajous.points[76].x = 2362;
		lissajous.points[76].y = 2520;
		lissajous.points[76].suppressPreviousTrack = false;

		lissajous.points[77].x = 2336;
		lissajous.points[77].y = 2501;
		lissajous.points[77].suppressPreviousTrack = false;

		lissajous.points[78].x = 2310;
		lissajous.points[78].y = 2494;
		lissajous.points[78].suppressPreviousTrack = false;

		lissajous.points[79].x = 2246;
		lissajous.points[79].y = 2507;
		lissajous.points[79].suppressPreviousTrack = false;

		lissajous.points[80].x = 2234;
		lissajous.points[80].y = 2488;
		lissajous.points[80].suppressPreviousTrack = false;

		lissajous.points[81].x = 2272;
		lissajous.points[81].y = 2424;
		lissajous.points[81].suppressPreviousTrack = false;

		lissajous.points[82].x = 2336;
		lissajous.points[82].y = 2315;
		lissajous.points[82].suppressPreviousTrack = false;

		lissajous.points[83].x = 2387;
		lissajous.points[83].y = 2226;
		lissajous.points[83].suppressPreviousTrack = false;

		lissajous.points[84].x = 2458;
		lissajous.points[84].y = 2117;
		lissajous.points[84].suppressPreviousTrack = false;

		lissajous.points[85].x = 2534;
		lissajous.points[85].y = 2027;
		lissajous.points[85].suppressPreviousTrack = false;

		lissajous.points[86].x = 2592;
		lissajous.points[86].y = 1957;
		lissajous.points[86].suppressPreviousTrack = false;

		lissajous.points[87].x = 2624;
		lissajous.points[87].y = 1912;
		lissajous.points[87].suppressPreviousTrack = false;

		lissajous.points[88].x = 2630;
		lissajous.points[88].y = 1861;
		lissajous.points[88].suppressPreviousTrack = false;

		lissajous.points[89].x = 2605;
		lissajous.points[89].y = 1854;
		lissajous.points[89].suppressPreviousTrack = false;

		lissajous.points[90].x = 2573;
		lissajous.points[90].y = 1848;
		lissajous.points[90].suppressPreviousTrack = false;

		lissajous.points[91].x = 2445;
		lissajous.points[91].y = 1854;
		lissajous.points[91].suppressPreviousTrack = false;

		lissajous.points[92].x = 2490;
		lissajous.points[92].y = 1790;
		lissajous.points[92].suppressPreviousTrack = false;

		lissajous.points[93].x = 2541;
		lissajous.points[93].y = 1701;
		lissajous.points[93].suppressPreviousTrack = false;

		lissajous.points[94].x = 2598;
		lissajous.points[94].y = 1605;
		lissajous.points[94].suppressPreviousTrack = false;

		lissajous.points[95].x = 2682;
		lissajous.points[95].y = 1509;
		lissajous.points[95].suppressPreviousTrack = false;

		lissajous.points[96].x = 2765;
		lissajous.points[96].y = 1406;
		lissajous.points[96].suppressPreviousTrack = false;

		lissajous.points[97].x = 2899;
		lissajous.points[97].y = 1253;
		lissajous.points[97].suppressPreviousTrack = false;

		lissajous.points[98].x = 2995;
		lissajous.points[98].y = 1150;
		lissajous.points[98].suppressPreviousTrack = false;

		lissajous.points[99].x = 3072;
		lissajous.points[99].y = 1074;
		lissajous.points[99].suppressPreviousTrack = false;

		lissajous.points[100].x = 3104;
		lissajous.points[100].y = 1035;
		lissajous.points[100].suppressPreviousTrack = false;

		lissajous.points[101].x = 3091;
		lissajous.points[101].y = 1010;
		lissajous.points[101].suppressPreviousTrack = false;

		lissajous.points[102].x = 3066;
		lissajous.points[102].y = 984;
		lissajous.points[102].suppressPreviousTrack = false;

		lissajous.points[103].x = 3002;
		lissajous.points[103].y = 984;
		lissajous.points[103].suppressPreviousTrack = false;

		lissajous.points[104].x = 2880;
		lissajous.points[104].y = 1016;
		lissajous.points[104].suppressPreviousTrack = false;

		lissajous.points[105].x = 2784;
		lissajous.points[105].y = 1035;
		lissajous.points[105].suppressPreviousTrack = false;

		lissajous.points[106].x = 2611;
		lissajous.points[106].y = 1054;
		lissajous.points[106].suppressPreviousTrack = false;

		lissajous.points[107].x = 2464;
		lissajous.points[107].y = 1067;
		lissajous.points[107].suppressPreviousTrack = false;

		lissajous.points[108].x = 2374;
		lissajous.points[108].y = 1067;
		lissajous.points[108].suppressPreviousTrack = false;

		lissajous.points[109].x = 2291;
		lissajous.points[109].y = 1048;
		lissajous.points[109].suppressPreviousTrack = false;

		lissajous.points[110].x = 2176;
		lissajous.points[110].y = 1048;
		lissajous.points[110].suppressPreviousTrack = false;

		lissajous.points[111].x = 2246;
		lissajous.points[111].y = 421;
		lissajous.points[111].suppressPreviousTrack = false;

		lissajous.points[112].x = 1850;
		lissajous.points[112].y = 427;
		lissajous.points[112].suppressPreviousTrack = false;

		lissajous.points[113].x = 1696;
		lissajous.points[113].y = 1426;
		lissajous.points[113].suppressPreviousTrack = true;

		lissajous.points[114].x = 1709;
		lissajous.points[114].y = 1496;
		lissajous.points[114].suppressPreviousTrack = false;

		lissajous.points[115].x = 1645;
		lissajous.points[115].y = 1534;
		lissajous.points[115].suppressPreviousTrack = false;

		lissajous.points[116].x = 1722;
		lissajous.points[116].y = 1541;
		lissajous.points[116].suppressPreviousTrack = false;

		lissajous.points[117].x = 1741;
		lissajous.points[117].y = 1611;
		lissajous.points[117].suppressPreviousTrack = false;

		lissajous.points[118].x = 1766;
		lissajous.points[118].y = 1554;
		lissajous.points[118].suppressPreviousTrack = false;

		lissajous.points[119].x = 1843;
		lissajous.points[119].y = 1541;
		lissajous.points[119].suppressPreviousTrack = false;

		lissajous.points[120].x = 1786;
		lissajous.points[120].y = 1483;
		lissajous.points[120].suppressPreviousTrack = false;

		lissajous.points[121].x = 1811;
		lissajous.points[121].y = 1432;
		lissajous.points[121].suppressPreviousTrack = false;

		lissajous.points[122].x = 1747;
		lissajous.points[122].y = 1464;
		lissajous.points[122].suppressPreviousTrack = false;

		lissajous.points[123].x = 1696;
		lissajous.points[123].y = 1426;
		lissajous.points[123].suppressPreviousTrack = false;

		lissajous.points[124].x = 2112;
		lissajous.points[124].y = 2078;
		lissajous.points[124].suppressPreviousTrack = true;

		lissajous.points[125].x = 2144;
		lissajous.points[125].y = 2117;
		lissajous.points[125].suppressPreviousTrack = false;

		lissajous.points[126].x = 2099;
		lissajous.points[126].y = 2123;
		lissajous.points[126].suppressPreviousTrack = false;

		lissajous.points[127].x = 2074;
		lissajous.points[127].y = 2123;
		lissajous.points[127].suppressPreviousTrack = false;

		lissajous.points[128].x = 2150;
		lissajous.points[128].y = 2155;
		lissajous.points[128].suppressPreviousTrack = false;

		lissajous.points[129].x = 2170;
		lissajous.points[129].y = 2226;
		lissajous.points[129].suppressPreviousTrack = false;

		lissajous.points[130].x = 2214;
		lissajous.points[130].y = 2149;
		lissajous.points[130].suppressPreviousTrack = false;

		lissajous.points[131].x = 2285;
		lissajous.points[131].y = 2136;
		lissajous.points[131].suppressPreviousTrack = false;

		lissajous.points[132].x = 2214;
		lissajous.points[132].y = 2104;
		lissajous.points[132].suppressPreviousTrack = false;

		lissajous.points[133].x = 2208;
		lissajous.points[133].y = 2008;
		lissajous.points[133].suppressPreviousTrack = false;

		lissajous.points[134].x = 2170;
		lissajous.points[134].y = 2104;
		lissajous.points[134].suppressPreviousTrack = false;

		lissajous.points[135].x = 2131;
		lissajous.points[135].y = 2130;
		lissajous.points[135].suppressPreviousTrack = false;		

		// Figuur afsluiten met kopie van eerste punt.
		lissajous.points[136].x = 1850;
		lissajous.points[136].y = 421;
		lissajous.points[136].suppressPreviousTrack = true;

		// Aantal punten megeven.
		lissajous.length = 137;
	}
	#endif
	
	#ifdef VIVES
	{
		lissajous.points[0].x = 296;
		lissajous.points[0].y = 1667;
		lissajous.points[0].suppressPreviousTrack = false;

		lissajous.points[1].x = 21;
		lissajous.points[1].y = 2442;
		lissajous.points[1].suppressPreviousTrack = false;

		lissajous.points[2].x = 251;
		lissajous.points[2].y = 2442;
		lissajous.points[2].suppressPreviousTrack = false;

		lissajous.points[3].x = 437;
		lissajous.points[3].y = 1917;
		lissajous.points[3].suppressPreviousTrack = false;

		lissajous.points[4].x = 616;
		lissajous.points[4].y = 2442;
		lissajous.points[4].suppressPreviousTrack = false;

		lissajous.points[5].x = 866;
		lissajous.points[5].y = 2435;
		lissajous.points[5].suppressPreviousTrack = false;

		lissajous.points[6].x = 578;
		lissajous.points[6].y = 1674;
		lissajous.points[6].suppressPreviousTrack = false;

		lissajous.points[7].x = 296;
		lissajous.points[7].y = 1674;
		lissajous.points[7].suppressPreviousTrack = false;

		lissajous.points[8].x = 923;
		lissajous.points[8].y = 1693;
		lissajous.points[8].suppressPreviousTrack = true;

		lissajous.points[9].x = 930;
		lissajous.points[9].y = 2435;
		lissajous.points[9].suppressPreviousTrack = false;

		lissajous.points[10].x = 1154;
		lissajous.points[10].y = 2442;
		lissajous.points[10].suppressPreviousTrack = false;

		lissajous.points[11].x = 1166;
		lissajous.points[11].y = 1674;
		lissajous.points[11].suppressPreviousTrack = false;

		lissajous.points[12].x = 923;
		lissajous.points[12].y = 1667;
		lissajous.points[12].suppressPreviousTrack = false;

		lissajous.points[13].x = 1499;
		lissajous.points[13].y = 1667;
		lissajous.points[13].suppressPreviousTrack = true;

		lissajous.points[14].x = 1224;
		lissajous.points[14].y = 2435;
		lissajous.points[14].suppressPreviousTrack = false;

		lissajous.points[15].x = 1474;
		lissajous.points[15].y = 2442;
		lissajous.points[15].suppressPreviousTrack = false;

		lissajous.points[16].x = 1646;
		lissajous.points[16].y = 1904;
		lissajous.points[16].suppressPreviousTrack = false;

		lissajous.points[17].x = 1813;
		lissajous.points[17].y = 2435;
		lissajous.points[17].suppressPreviousTrack = false;

		lissajous.points[18].x = 2056;
		lissajous.points[18].y = 2442;
		lissajous.points[18].suppressPreviousTrack = false;

		lissajous.points[19].x = 1800;
		lissajous.points[19].y = 1680;
		lissajous.points[19].suppressPreviousTrack = false;

		lissajous.points[20].x = 1493;
		lissajous.points[20].y = 1667;
		lissajous.points[20].suppressPreviousTrack = false;

		lissajous.points[21].x = 2843;
		lissajous.points[21].y = 1923;
		lissajous.points[21].suppressPreviousTrack = true;

		lissajous.points[22].x = 2606;
		lissajous.points[22].y = 1930;
		lissajous.points[22].suppressPreviousTrack = false;

		lissajous.points[23].x = 2587;
		lissajous.points[23].y = 1917;
		lissajous.points[23].suppressPreviousTrack = false;

		lissajous.points[24].x = 2562;
		lissajous.points[24].y = 1891;
		lissajous.points[24].suppressPreviousTrack = false;

		lissajous.points[25].x = 2510;
		lissajous.points[25].y = 1866;
		lissajous.points[25].suppressPreviousTrack = false;

		lissajous.points[26].x = 2434;
		lissajous.points[26].y = 1853;
		lissajous.points[26].suppressPreviousTrack = false;

		lissajous.points[27].x = 2382;
		lissajous.points[27].y = 1872;
		lissajous.points[27].suppressPreviousTrack = false;

		lissajous.points[28].x = 2338;
		lissajous.points[28].y = 1910;
		lissajous.points[28].suppressPreviousTrack = false;

		lissajous.points[29].x = 2318;
		lissajous.points[29].y = 1942;
		lissajous.points[29].suppressPreviousTrack = false;

		lissajous.points[30].x = 2318;
		lissajous.points[30].y = 1994;
		lissajous.points[30].suppressPreviousTrack = false;

		lissajous.points[31].x = 2862;
		lissajous.points[31].y = 1994;
		lissajous.points[31].suppressPreviousTrack = false;

		lissajous.points[32].x = 2869;
		lissajous.points[32].y = 2058;
		lissajous.points[32].suppressPreviousTrack = false;

		lissajous.points[33].x = 2869;
		lissajous.points[33].y = 2109;
		lissajous.points[33].suppressPreviousTrack = false;

		lissajous.points[34].x = 2862;
		lissajous.points[34].y = 2179;
		lissajous.points[34].suppressPreviousTrack = false;

		lissajous.points[35].x = 2830;
		lissajous.points[35].y = 2243;
		lissajous.points[35].suppressPreviousTrack = false;

		lissajous.points[36].x = 2798;
		lissajous.points[36].y = 2301;
		lissajous.points[36].suppressPreviousTrack = false;

		lissajous.points[37].x = 2734;
		lissajous.points[37].y = 2358;
		lissajous.points[37].suppressPreviousTrack = false;

		lissajous.points[38].x = 2645;
		lissajous.points[38].y = 2429;
		lissajous.points[38].suppressPreviousTrack = false;

		lissajous.points[39].x = 2555;
		lissajous.points[39].y = 2448;
		lissajous.points[39].suppressPreviousTrack = false;

		lissajous.points[40].x = 2498;
		lissajous.points[40].y = 2461;
		lissajous.points[40].suppressPreviousTrack = false;

		lissajous.points[41].x = 2395;
		lissajous.points[41].y = 2461;
		lissajous.points[41].suppressPreviousTrack = false;

		lissajous.points[42].x = 2331;
		lissajous.points[42].y = 2435;
		lissajous.points[42].suppressPreviousTrack = false;

		lissajous.points[43].x = 2261;
		lissajous.points[43].y = 2403;
		lissajous.points[43].suppressPreviousTrack = false;

		lissajous.points[44].x = 2203;
		lissajous.points[44].y = 2365;
		lissajous.points[44].suppressPreviousTrack = false;

		lissajous.points[45].x = 2152;
		lissajous.points[45].y = 2314;
		lissajous.points[45].suppressPreviousTrack = false;

		lissajous.points[46].x = 2101;
		lissajous.points[46].y = 2218;
		lissajous.points[46].suppressPreviousTrack = false;

		lissajous.points[47].x = 2082;
		lissajous.points[47].y = 2122;
		lissajous.points[47].suppressPreviousTrack = false;

		lissajous.points[48].x = 2082;
		lissajous.points[48].y = 2006;
		lissajous.points[48].suppressPreviousTrack = false;

		lissajous.points[49].x = 2114;
		lissajous.points[49].y = 1878;
		lissajous.points[49].suppressPreviousTrack = false;

		lissajous.points[50].x = 2165;
		lissajous.points[50].y = 1814;
		lissajous.points[50].suppressPreviousTrack = false;

		lissajous.points[51].x = 2229;
		lissajous.points[51].y = 1763;
		lissajous.points[51].suppressPreviousTrack = false;

		lissajous.points[52].x = 2306;
		lissajous.points[52].y = 1712;
		lissajous.points[52].suppressPreviousTrack = false;

		lissajous.points[53].x = 2389;
		lissajous.points[53].y = 1680;
		lissajous.points[53].suppressPreviousTrack = false;

		lissajous.points[54].x = 2466;
		lissajous.points[54].y = 1661;
		lissajous.points[54].suppressPreviousTrack = false;

		lissajous.points[55].x = 2555;
		lissajous.points[55].y = 1661;
		lissajous.points[55].suppressPreviousTrack = false;

		lissajous.points[56].x = 2626;
		lissajous.points[56].y = 1667;
		lissajous.points[56].suppressPreviousTrack = false;

		lissajous.points[57].x = 2709;
		lissajous.points[57].y = 1712;
		lissajous.points[57].suppressPreviousTrack = false;

		lissajous.points[58].x = 2773;
		lissajous.points[58].y = 1763;
		lissajous.points[58].suppressPreviousTrack = false;

		lissajous.points[59].x = 2824;
		lissajous.points[59].y = 1859;
		lissajous.points[59].suppressPreviousTrack = false;

		lissajous.points[60].x = 2837;
		lissajous.points[60].y = 1917;
		lissajous.points[60].suppressPreviousTrack = false;

		lissajous.points[61].x = 2626;
		lissajous.points[61].y = 2147;
		lissajous.points[61].suppressPreviousTrack = true;

		lissajous.points[62].x = 2331;
		lissajous.points[62].y = 2179;
		lissajous.points[62].suppressPreviousTrack = false;

		lissajous.points[63].x = 2350;
		lissajous.points[63].y = 2224;
		lissajous.points[63].suppressPreviousTrack = false;

		lissajous.points[64].x = 2421;
		lissajous.points[64].y = 2262;
		lissajous.points[64].suppressPreviousTrack = false;

		lissajous.points[65].x = 2485;
		lissajous.points[65].y = 2262;
		lissajous.points[65].suppressPreviousTrack = false;

		lissajous.points[66].x = 2594;
		lissajous.points[66].y = 2205;
		lissajous.points[66].suppressPreviousTrack = false;

		lissajous.points[67].x = 2606;
		lissajous.points[67].y = 2166;
		lissajous.points[67].suppressPreviousTrack = false;

		lissajous.points[68].x = 2619;
		lissajous.points[68].y = 2122;
		lissajous.points[68].suppressPreviousTrack = false;

		lissajous.points[69].x = 2907;
		lissajous.points[69].y = 1923;
		lissajous.points[69].suppressPreviousTrack = true;

		lissajous.points[70].x = 3144;
		lissajous.points[70].y = 1923;
		lissajous.points[70].suppressPreviousTrack = false;

		lissajous.points[71].x = 3163;
		lissajous.points[71].y = 1878;
		lissajous.points[71].suppressPreviousTrack = false;

		lissajous.points[72].x = 3214;
		lissajous.points[72].y = 1840;
		lissajous.points[72].suppressPreviousTrack = false;

		lissajous.points[73].x = 3272;
		lissajous.points[73].y = 1834;
		lissajous.points[73].suppressPreviousTrack = false;

		lissajous.points[74].x = 3330;
		lissajous.points[74].y = 1846;
		lissajous.points[74].suppressPreviousTrack = false;

		lissajous.points[75].x = 3368;
		lissajous.points[75].y = 1891;
		lissajous.points[75].suppressPreviousTrack = false;

		lissajous.points[76].x = 3355;
		lissajous.points[76].y = 1949;
		lissajous.points[76].suppressPreviousTrack = false;

		lissajous.points[77].x = 3310;
		lissajous.points[77].y = 1968;
		lissajous.points[77].suppressPreviousTrack = false;

		lissajous.points[78].x = 3144;
		lissajous.points[78].y = 2013;
		lissajous.points[78].suppressPreviousTrack = false;

		lissajous.points[79].x = 3048;
		lissajous.points[79].y = 2038;
		lissajous.points[79].suppressPreviousTrack = false;

		lissajous.points[80].x = 2978;
		lissajous.points[80].y = 2070;
		lissajous.points[80].suppressPreviousTrack = false;

		lissajous.points[81].x = 2926;
		lissajous.points[81].y = 2179;
		lissajous.points[81].suppressPreviousTrack = false;

		lissajous.points[82].x = 2958;
		lissajous.points[82].y = 2320;
		lissajous.points[82].suppressPreviousTrack = false;

		lissajous.points[83].x = 3010;
		lissajous.points[83].y = 2384;
		lissajous.points[83].suppressPreviousTrack = false;

		lissajous.points[84].x = 3054;
		lissajous.points[84].y = 2410;
		lissajous.points[84].suppressPreviousTrack = false;

		lissajous.points[85].x = 3125;
		lissajous.points[85].y = 2435;
		lissajous.points[85].suppressPreviousTrack = false;

		lissajous.points[86].x = 3221;
		lissajous.points[86].y = 2448;
		lissajous.points[86].suppressPreviousTrack = false;

		lissajous.points[87].x = 3291;
		lissajous.points[87].y = 2448;
		lissajous.points[87].suppressPreviousTrack = false;

		lissajous.points[88].x = 3368;
		lissajous.points[88].y = 2435;
		lissajous.points[88].suppressPreviousTrack = false;

		lissajous.points[89].x = 3426;
		lissajous.points[89].y = 2422;
		lissajous.points[89].suppressPreviousTrack = false;

		lissajous.points[90].x = 3490;
		lissajous.points[90].y = 2378;
		lissajous.points[90].suppressPreviousTrack = false;

		lissajous.points[91].x = 3515;
		lissajous.points[91].y = 2339;
		lissajous.points[91].suppressPreviousTrack = false;

		lissajous.points[92].x = 3547;
		lissajous.points[92].y = 2282;
		lissajous.points[92].suppressPreviousTrack = false;

		lissajous.points[93].x = 3573;
		lissajous.points[93].y = 2211;
		lissajous.points[93].suppressPreviousTrack = false;

		lissajous.points[94].x = 3573;
		lissajous.points[94].y = 2192;
		lissajous.points[94].suppressPreviousTrack = false;

		lissajous.points[95].x = 3368;
		lissajous.points[95].y = 2173;
		lissajous.points[95].suppressPreviousTrack = false;

		lissajous.points[96].x = 3355;
		lissajous.points[96].y = 2205;
		lissajous.points[96].suppressPreviousTrack = false;

		lissajous.points[97].x = 3317;
		lissajous.points[97].y = 2256;
		lissajous.points[97].suppressPreviousTrack = false;

		lissajous.points[98].x = 3310;
		lissajous.points[98].y = 2256;
		lissajous.points[98].suppressPreviousTrack = false;

		lissajous.points[99].x = 3253;
		lissajous.points[99].y = 2275;
		lissajous.points[99].suppressPreviousTrack = false;

		lissajous.points[100].x = 3195;
		lissajous.points[100].y = 2275;
		lissajous.points[100].suppressPreviousTrack = false;

		lissajous.points[101].x = 3170;
		lissajous.points[101].y = 2243;
		lissajous.points[101].suppressPreviousTrack = false;

		lissajous.points[102].x = 3163;
		lissajous.points[102].y = 2205;
		lissajous.points[102].suppressPreviousTrack = false;

		lissajous.points[103].x = 3195;
		lissajous.points[103].y = 2173;
		lissajous.points[103].suppressPreviousTrack = false;

		lissajous.points[104].x = 3266;
		lissajous.points[104].y = 2147;
		lissajous.points[104].suppressPreviousTrack = false;

		lissajous.points[105].x = 3374;
		lissajous.points[105].y = 2115;
		lissajous.points[105].suppressPreviousTrack = false;

		lissajous.points[106].x = 3470;
		lissajous.points[106].y = 2083;
		lissajous.points[106].suppressPreviousTrack = false;

		lissajous.points[107].x = 3522;
		lissajous.points[107].y = 2051;
		lissajous.points[107].suppressPreviousTrack = false;

		lissajous.points[108].x = 3560;
		lissajous.points[108].y = 1994;
		lissajous.points[108].suppressPreviousTrack = false;

		lissajous.points[109].x = 3586;
		lissajous.points[109].y = 1917;
		lissajous.points[109].suppressPreviousTrack = false;

		lissajous.points[110].x = 3579;
		lissajous.points[110].y = 1834;
		lissajous.points[110].suppressPreviousTrack = false;

		lissajous.points[111].x = 3528;
		lissajous.points[111].y = 1744;
		lissajous.points[111].suppressPreviousTrack = false;

		lissajous.points[112].x = 3477;
		lissajous.points[112].y = 1712;
		lissajous.points[112].suppressPreviousTrack = false;

		lissajous.points[113].x = 3394;
		lissajous.points[113].y = 1680;
		lissajous.points[113].suppressPreviousTrack = false;

		lissajous.points[114].x = 3291;
		lissajous.points[114].y = 1654;
		lissajous.points[114].suppressPreviousTrack = false;

		lissajous.points[115].x = 3214;
		lissajous.points[115].y = 1654;
		lissajous.points[115].suppressPreviousTrack = false;

		lissajous.points[116].x = 3131;
		lissajous.points[116].y = 1674;
		lissajous.points[116].suppressPreviousTrack = false;

		lissajous.points[117].x = 3067;
		lissajous.points[117].y = 1706;
		lissajous.points[117].suppressPreviousTrack = false;

		lissajous.points[118].x = 3016;
		lissajous.points[118].y = 1738;
		lissajous.points[118].suppressPreviousTrack = false;

		lissajous.points[119].x = 2952;
		lissajous.points[119].y = 1814;
		lissajous.points[119].suppressPreviousTrack = false;

		lissajous.points[120].x = 2920;
		lissajous.points[120].y = 1898;
		lissajous.points[120].suppressPreviousTrack = false;

		// Figuur afsluiten met kopie van eerste punt.
		lissajous.points[121].x = 296;
		lissajous.points[121].y = 1667;
		lissajous.points[121].suppressPreviousTrack = true;
		
		// Aantal punten megeven.
		lissajous.length = 122;
	}
	#endif
	
	#ifdef RECTANGLE
	{
		lissajous.points[0].x = 674;
		lissajous.points[0].y = 862;
		lissajous.points[0].suppressPreviousTrack = false;
		lissajous.points[1].x = 629;
		lissajous.points[1].y = 2974;
		lissajous.points[1].suppressPreviousTrack = false;
		lissajous.points[2].x = 3150;
		lissajous.points[2].y = 2930;
		lissajous.points[2].suppressPreviousTrack = false;
		lissajous.points[3].x = 3138;
		lissajous.points[3].y = 798;
		lissajous.points[3].suppressPreviousTrack = false;
		
		
		// Figuur afsluiten met kopie van eerste punt.
		lissajous.points[4].x = 674;
		lissajous.points[4].y = 862;
		lissajous.points[4].suppressPreviousTrack = false;

		// Aantal punten megeven.
		lissajous.length = 5;
	}
	#endif
	
	while (1)
	{	
		#ifdef MEASURE_LOOP_TIME
			// Lustijd meten (optioneel).
			startTicks = ticks;
		#endif
		
		// Teken de volledige figuur... Duurt ongeveer 15ms voor de Kerstboom (vastgesteld via meting).
		DrawLissajous(&lissajous, lissajous.length);		
		
		#ifdef MEASURE_LOOP_TIME
			// Lustijd meten (optioneel).
			deltaTicks = ticks - startTicks;		
			sprintf(text, "Loop time: %d ms.\r\n", deltaTicks);
			StringToUsart2(text);
		#endif
	}
}

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
