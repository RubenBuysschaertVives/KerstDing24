// Defines.
//#define MEASURE_LOOP_TIME
// Kies een afbeelding.
#define KERSTBOOM
//#define VIVES
//#define RECTANGLE
#define PEACE

#define SERVO_JUST_BELOW_MIDPOINT 1450			// Normaal middelpunt is 1500/2000. Doe daar een kleinigheid af zodat je later kan bijregelen met de on board potentiometer.
#define SERVO_SPEED	75											// Snelheid van de servo instellen (in 2000-sten).
#define AD_DIVIDER 40												// 12-bit AD-waarde herschalen.
#define LOOP_DELAY 10												// Hoofdlus niet sneller dan iedere 10ms doorlopen.
#define ERROR_TIMEOUT 9000									// Na 9 seconden geen m&m, stop sowieso.

// Header files toevoegen.
#include "stm32f091xc.h"
#include "stdio.h"
#include "stdbool.h"
#include "usart2.h"
#include "dac.h"
#include "lissajous.h"
#include "leds.h"
#include "buttons.h"
#include "ad.h"
#include "pwm.h"
#include "ir.h"

// Functie prototypes aanmaken.
void SystemClock_Config(void);
void WaitForMs(uint32_t timespan);
void DrawLissajous(Lissajous* lissajousXmas, uint16_t count);

// Globale variabelen.
static uint16_t i = 0;
static volatile uint32_t ticks = 0;
#ifdef MEASURE_LOOP_TIME
	static uint32_t startTicks = 0, deltaTicks = 0;
#endif
static char text[101];
static Lissajous lissajousXmas, lissajousRectangle, lissajousPeace;
static bool IR1Help = false, run = false, sw1Help = false;
static uint16_t count = 0, wannabeTimer = 0;
static uint16_t adValue = 0;

// Entry point.
int main(void)
{
	// Initialisaties.
	SystemClock_Config();
	InitUsart2(115200);
	InitDAC();
	InitButtons();
	InitLeds();
	InitAd();
	InitPwm();
	InitIRs();

	// 0 -> 4095
	adValue = GetAdValue();
	
	// 0 -> 100
	adValue /= AD_DIVIDER;
	
	// Nulpunt instellen via AD-converter en on board potentiometer.
	// Het nulpunt zorgt ervoor dat de 'continuous rotation servo' stil kan staan.
	SetPwm(SERVO_JUST_BELOW_MIDPOINT + adValue);
	
	// Berichtje op de UART (optioneel).
	sprintf(text, "KerstDing24 - Lissajous figuren via DAC's en m&m op een Nucleo-F091RC.\r\n");
	StringToUsart2(text);
	
	// Analoge spanningen op nul volt zetten.
	SetDacX(0);
	SetDacY(0);
	
	// Data initialiseren op nul (optioneel).
	for(i = 0; i < MAX_NUMBER_OF_POINTS; i++)
	{
		lissajousXmas.points[i].x = 0;
		lissajousXmas.points[i].y = 0;
		lissajousXmas.points[i].suppressPreviousTrack = false;
		
		lissajousRectangle.points[i].x = 0;
		lissajousRectangle.points[i].y = 0;
		lissajousRectangle.points[i].suppressPreviousTrack = false;
	}

	// Data opvullen.
	#ifdef KERSTBOOM
	{
		lissajousXmas.points[0].x = 1850;
		lissajousXmas.points[0].y = 421;
		lissajousXmas.points[0].suppressPreviousTrack = false;

		lissajousXmas.points[1].x = 1914;
		lissajousXmas.points[1].y = 1010;
		lissajousXmas.points[1].suppressPreviousTrack = false;

		lissajousXmas.points[2].x = 1843;
		lissajousXmas.points[2].y = 1010;
		lissajousXmas.points[2].suppressPreviousTrack = false;

		lissajousXmas.points[3].x = 1766;
		lissajousXmas.points[3].y = 1003;
		lissajousXmas.points[3].suppressPreviousTrack = false;

		lissajousXmas.points[4].x = 1677;
		lissajousXmas.points[4].y = 990;
		lissajousXmas.points[4].suppressPreviousTrack = false;

		lissajousXmas.points[5].x = 1600;
		lissajousXmas.points[5].y = 978;
		lissajousXmas.points[5].suppressPreviousTrack = false;

		lissajousXmas.points[6].x = 1510;
		lissajousXmas.points[6].y = 971;
		lissajousXmas.points[6].suppressPreviousTrack = false;

		lissajousXmas.points[7].x = 1376;
		lissajousXmas.points[7].y = 971;
		lissajousXmas.points[7].suppressPreviousTrack = false;

		lissajousXmas.points[8].x = 1318;
		lissajousXmas.points[8].y = 965;
		lissajousXmas.points[8].suppressPreviousTrack = false;

		lissajousXmas.points[9].x = 1222;
		lissajousXmas.points[9].y = 971;
		lissajousXmas.points[9].suppressPreviousTrack = false;

		lissajousXmas.points[10].x = 1171;
		lissajousXmas.points[10].y = 978;
		lissajousXmas.points[10].suppressPreviousTrack = false;

		lissajousXmas.points[11].x = 1094;
		lissajousXmas.points[11].y = 984;
		lissajousXmas.points[11].suppressPreviousTrack = false;

		lissajousXmas.points[12].x = 1018;
		lissajousXmas.points[12].y = 997;
		lissajousXmas.points[12].suppressPreviousTrack = false;

		lissajousXmas.points[13].x = 998;
		lissajousXmas.points[13].y = 1016;
		lissajousXmas.points[13].suppressPreviousTrack = false;

		lissajousXmas.points[14].x = 998;
		lissajousXmas.points[14].y = 1054;
		lissajousXmas.points[14].suppressPreviousTrack = false;

		lissajousXmas.points[15].x = 1005;
		lissajousXmas.points[15].y = 1086;
		lissajousXmas.points[15].suppressPreviousTrack = false;

		lissajousXmas.points[16].x = 1050;
		lissajousXmas.points[16].y = 1112;
		lissajousXmas.points[16].suppressPreviousTrack = false;

		lissajousXmas.points[17].x = 1146;
		lissajousXmas.points[17].y = 1195;
		lissajousXmas.points[17].suppressPreviousTrack = false;

		lissajousXmas.points[18].x = 1210;
		lissajousXmas.points[18].y = 1291;
		lissajousXmas.points[18].suppressPreviousTrack = false;

		lissajousXmas.points[19].x = 1267;
		lissajousXmas.points[19].y = 1336;
		lissajousXmas.points[19].suppressPreviousTrack = false;

		lissajousXmas.points[20].x = 1344;
		lissajousXmas.points[20].y = 1419;
		lissajousXmas.points[20].suppressPreviousTrack = false;

		lissajousXmas.points[21].x = 1402;
		lissajousXmas.points[21].y = 1502;
		lissajousXmas.points[21].suppressPreviousTrack = false;

		lissajousXmas.points[22].x = 1459;
		lissajousXmas.points[22].y = 1573;
		lissajousXmas.points[22].suppressPreviousTrack = false;

		lissajousXmas.points[23].x = 1510;
		lissajousXmas.points[23].y = 1643;
		lissajousXmas.points[23].suppressPreviousTrack = false;

		lissajousXmas.points[24].x = 1581;
		lissajousXmas.points[24].y = 1733;
		lissajousXmas.points[24].suppressPreviousTrack = false;

		lissajousXmas.points[25].x = 1613;
		lissajousXmas.points[25].y = 1790;
		lissajousXmas.points[25].suppressPreviousTrack = false;

		lissajousXmas.points[26].x = 1658;
		lissajousXmas.points[26].y = 1842;
		lissajousXmas.points[26].suppressPreviousTrack = false;

		lissajousXmas.points[27].x = 1670;
		lissajousXmas.points[27].y = 1880;
		lissajousXmas.points[27].suppressPreviousTrack = false;

		lissajousXmas.points[28].x = 1638;
		lissajousXmas.points[28].y = 1880;
		lissajousXmas.points[28].suppressPreviousTrack = false;

		lissajousXmas.points[29].x = 1587;
		lissajousXmas.points[29].y = 1880;
		lissajousXmas.points[29].suppressPreviousTrack = false;

		lissajousXmas.points[30].x = 1523;
		lissajousXmas.points[30].y = 1880;
		lissajousXmas.points[30].suppressPreviousTrack = false;

		lissajousXmas.points[31].x = 1472;
		lissajousXmas.points[31].y = 1874;
		lissajousXmas.points[31].suppressPreviousTrack = false;

		lissajousXmas.points[32].x = 1466;
		lissajousXmas.points[32].y = 1893;
		lissajousXmas.points[32].suppressPreviousTrack = false;

		lissajousXmas.points[33].x = 1466;
		lissajousXmas.points[33].y = 1925;
		lissajousXmas.points[33].suppressPreviousTrack = false;

		lissajousXmas.points[34].x = 1498;
		lissajousXmas.points[34].y = 1963;
		lissajousXmas.points[34].suppressPreviousTrack = false;

		lissajousXmas.points[35].x = 1542;
		lissajousXmas.points[35].y = 2014;
		lissajousXmas.points[35].suppressPreviousTrack = false;

		lissajousXmas.points[36].x = 1613;
		lissajousXmas.points[36].y = 2091;
		lissajousXmas.points[36].suppressPreviousTrack = false;

		lissajousXmas.points[37].x = 1664;
		lissajousXmas.points[37].y = 2162;
		lissajousXmas.points[37].suppressPreviousTrack = false;

		lissajousXmas.points[38].x = 1734;
		lissajousXmas.points[38].y = 2270;
		lissajousXmas.points[38].suppressPreviousTrack = false;

		lissajousXmas.points[39].x = 1792;
		lissajousXmas.points[39].y = 2360;
		lissajousXmas.points[39].suppressPreviousTrack = false;

		lissajousXmas.points[40].x = 1811;
		lissajousXmas.points[40].y = 2405;
		lissajousXmas.points[40].suppressPreviousTrack = false;

		lissajousXmas.points[41].x = 1830;
		lissajousXmas.points[41].y = 2456;
		lissajousXmas.points[41].suppressPreviousTrack = false;

		lissajousXmas.points[42].x = 1856;
		lissajousXmas.points[42].y = 2520;
		lissajousXmas.points[42].suppressPreviousTrack = false;

		lissajousXmas.points[43].x = 1843;
		lissajousXmas.points[43].y = 2526;
		lissajousXmas.points[43].suppressPreviousTrack = false;

		lissajousXmas.points[44].x = 1811;
		lissajousXmas.points[44].y = 2526;
		lissajousXmas.points[44].suppressPreviousTrack = false;

		lissajousXmas.points[45].x = 1766;
		lissajousXmas.points[45].y = 2526;
		lissajousXmas.points[45].suppressPreviousTrack = false;

		lissajousXmas.points[46].x = 1734;
		lissajousXmas.points[46].y = 2526;
		lissajousXmas.points[46].suppressPreviousTrack = false;

		lissajousXmas.points[47].x = 1728;
		lissajousXmas.points[47].y = 2546;
		lissajousXmas.points[47].suppressPreviousTrack = false;

		lissajousXmas.points[48].x = 1734;
		lissajousXmas.points[48].y = 2590;
		lissajousXmas.points[48].suppressPreviousTrack = false;

		lissajousXmas.points[49].x = 1766;
		lissajousXmas.points[49].y = 2642;
		lissajousXmas.points[49].suppressPreviousTrack = false;

		lissajousXmas.points[50].x = 1811;
		lissajousXmas.points[50].y = 2706;
		lissajousXmas.points[50].suppressPreviousTrack = false;

		lissajousXmas.points[51].x = 1856;
		lissajousXmas.points[51].y = 2789;
		lissajousXmas.points[51].suppressPreviousTrack = false;

		lissajousXmas.points[52].x = 1875;
		lissajousXmas.points[52].y = 2821;
		lissajousXmas.points[52].suppressPreviousTrack = false;

		lissajousXmas.points[53].x = 1920;
		lissajousXmas.points[53].y = 2923;
		lissajousXmas.points[53].suppressPreviousTrack = false;

		lissajousXmas.points[54].x = 1978;
		lissajousXmas.points[54].y = 3058;
		lissajousXmas.points[54].suppressPreviousTrack = false;

		lissajousXmas.points[55].x = 2048;
		lissajousXmas.points[55].y = 3243;
		lissajousXmas.points[55].suppressPreviousTrack = false;

		lissajousXmas.points[56].x = 2054;
		lissajousXmas.points[56].y = 3346;
		lissajousXmas.points[56].suppressPreviousTrack = true;

		lissajousXmas.points[57].x = 1926;
		lissajousXmas.points[57].y = 3256;
		lissajousXmas.points[57].suppressPreviousTrack = false;

		lissajousXmas.points[58].x = 1965;
		lissajousXmas.points[58].y = 3429;
		lissajousXmas.points[58].suppressPreviousTrack = false;

		lissajousXmas.points[59].x = 1837;
		lissajousXmas.points[59].y = 3512;
		lissajousXmas.points[59].suppressPreviousTrack = false;

		lissajousXmas.points[60].x = 1990;
		lissajousXmas.points[60].y = 3525;
		lissajousXmas.points[60].suppressPreviousTrack = false;

		lissajousXmas.points[61].x = 2048;
		lissajousXmas.points[61].y = 3678;
		lissajousXmas.points[61].suppressPreviousTrack = false;

		lissajousXmas.points[62].x = 2106;
		lissajousXmas.points[62].y = 3512;
		lissajousXmas.points[62].suppressPreviousTrack = false;

		lissajousXmas.points[63].x = 2266;
		lissajousXmas.points[63].y = 3512;
		lissajousXmas.points[63].suppressPreviousTrack = false;

		lissajousXmas.points[64].x = 2138;
		lissajousXmas.points[64].y = 3410;
		lissajousXmas.points[64].suppressPreviousTrack = false;

		lissajousXmas.points[65].x = 2182;
		lissajousXmas.points[65].y = 3250;
		lissajousXmas.points[65].suppressPreviousTrack = false;

		lissajousXmas.points[66].x = 2054;
		lissajousXmas.points[66].y = 3339;
		lissajousXmas.points[66].suppressPreviousTrack = false;

		lissajousXmas.points[67].x = 2054;
		lissajousXmas.points[67].y = 3243;
		lissajousXmas.points[67].suppressPreviousTrack = true;

		lissajousXmas.points[68].x = 2067;
		lissajousXmas.points[68].y = 3179;
		lissajousXmas.points[68].suppressPreviousTrack = false;

		lissajousXmas.points[69].x = 2112;
		lissajousXmas.points[69].y = 3070;
		lissajousXmas.points[69].suppressPreviousTrack = false;

		lissajousXmas.points[70].x = 2150;
		lissajousXmas.points[70].y = 2962;
		lissajousXmas.points[70].suppressPreviousTrack = false;

		lissajousXmas.points[71].x = 2202;
		lissajousXmas.points[71].y = 2846;
		lissajousXmas.points[71].suppressPreviousTrack = false;

		lissajousXmas.points[72].x = 2259;
		lissajousXmas.points[72].y = 2731;
		lissajousXmas.points[72].suppressPreviousTrack = false;

		lissajousXmas.points[73].x = 2310;
		lissajousXmas.points[73].y = 2629;
		lissajousXmas.points[73].suppressPreviousTrack = false;

		lissajousXmas.points[74].x = 2355;
		lissajousXmas.points[74].y = 2565;
		lissajousXmas.points[74].suppressPreviousTrack = false;

		lissajousXmas.points[75].x = 2362;
		lissajousXmas.points[75].y = 2546;
		lissajousXmas.points[75].suppressPreviousTrack = false;

		lissajousXmas.points[76].x = 2362;
		lissajousXmas.points[76].y = 2520;
		lissajousXmas.points[76].suppressPreviousTrack = false;

		lissajousXmas.points[77].x = 2336;
		lissajousXmas.points[77].y = 2501;
		lissajousXmas.points[77].suppressPreviousTrack = false;

		lissajousXmas.points[78].x = 2310;
		lissajousXmas.points[78].y = 2494;
		lissajousXmas.points[78].suppressPreviousTrack = false;

		lissajousXmas.points[79].x = 2246;
		lissajousXmas.points[79].y = 2507;
		lissajousXmas.points[79].suppressPreviousTrack = false;

		lissajousXmas.points[80].x = 2234;
		lissajousXmas.points[80].y = 2488;
		lissajousXmas.points[80].suppressPreviousTrack = false;

		lissajousXmas.points[81].x = 2272;
		lissajousXmas.points[81].y = 2424;
		lissajousXmas.points[81].suppressPreviousTrack = false;

		lissajousXmas.points[82].x = 2336;
		lissajousXmas.points[82].y = 2315;
		lissajousXmas.points[82].suppressPreviousTrack = false;

		lissajousXmas.points[83].x = 2387;
		lissajousXmas.points[83].y = 2226;
		lissajousXmas.points[83].suppressPreviousTrack = false;

		lissajousXmas.points[84].x = 2458;
		lissajousXmas.points[84].y = 2117;
		lissajousXmas.points[84].suppressPreviousTrack = false;

		lissajousXmas.points[85].x = 2534;
		lissajousXmas.points[85].y = 2027;
		lissajousXmas.points[85].suppressPreviousTrack = false;

		lissajousXmas.points[86].x = 2592;
		lissajousXmas.points[86].y = 1957;
		lissajousXmas.points[86].suppressPreviousTrack = false;

		lissajousXmas.points[87].x = 2624;
		lissajousXmas.points[87].y = 1912;
		lissajousXmas.points[87].suppressPreviousTrack = false;

		lissajousXmas.points[88].x = 2630;
		lissajousXmas.points[88].y = 1861;
		lissajousXmas.points[88].suppressPreviousTrack = false;

		lissajousXmas.points[89].x = 2605;
		lissajousXmas.points[89].y = 1854;
		lissajousXmas.points[89].suppressPreviousTrack = false;

		lissajousXmas.points[90].x = 2573;
		lissajousXmas.points[90].y = 1848;
		lissajousXmas.points[90].suppressPreviousTrack = false;

		lissajousXmas.points[91].x = 2445;
		lissajousXmas.points[91].y = 1854;
		lissajousXmas.points[91].suppressPreviousTrack = false;

		lissajousXmas.points[92].x = 2490;
		lissajousXmas.points[92].y = 1790;
		lissajousXmas.points[92].suppressPreviousTrack = false;

		lissajousXmas.points[93].x = 2541;
		lissajousXmas.points[93].y = 1701;
		lissajousXmas.points[93].suppressPreviousTrack = false;

		lissajousXmas.points[94].x = 2598;
		lissajousXmas.points[94].y = 1605;
		lissajousXmas.points[94].suppressPreviousTrack = false;

		lissajousXmas.points[95].x = 2682;
		lissajousXmas.points[95].y = 1509;
		lissajousXmas.points[95].suppressPreviousTrack = false;

		lissajousXmas.points[96].x = 2765;
		lissajousXmas.points[96].y = 1406;
		lissajousXmas.points[96].suppressPreviousTrack = false;

		lissajousXmas.points[97].x = 2899;
		lissajousXmas.points[97].y = 1253;
		lissajousXmas.points[97].suppressPreviousTrack = false;

		lissajousXmas.points[98].x = 2995;
		lissajousXmas.points[98].y = 1150;
		lissajousXmas.points[98].suppressPreviousTrack = false;

		lissajousXmas.points[99].x = 3072;
		lissajousXmas.points[99].y = 1074;
		lissajousXmas.points[99].suppressPreviousTrack = false;

		lissajousXmas.points[100].x = 3104;
		lissajousXmas.points[100].y = 1035;
		lissajousXmas.points[100].suppressPreviousTrack = false;

		lissajousXmas.points[101].x = 3091;
		lissajousXmas.points[101].y = 1010;
		lissajousXmas.points[101].suppressPreviousTrack = false;

		lissajousXmas.points[102].x = 3066;
		lissajousXmas.points[102].y = 984;
		lissajousXmas.points[102].suppressPreviousTrack = false;

		lissajousXmas.points[103].x = 3002;
		lissajousXmas.points[103].y = 984;
		lissajousXmas.points[103].suppressPreviousTrack = false;

		lissajousXmas.points[104].x = 2880;
		lissajousXmas.points[104].y = 1016;
		lissajousXmas.points[104].suppressPreviousTrack = false;

		lissajousXmas.points[105].x = 2784;
		lissajousXmas.points[105].y = 1035;
		lissajousXmas.points[105].suppressPreviousTrack = false;

		lissajousXmas.points[106].x = 2611;
		lissajousXmas.points[106].y = 1054;
		lissajousXmas.points[106].suppressPreviousTrack = false;

		lissajousXmas.points[107].x = 2464;
		lissajousXmas.points[107].y = 1067;
		lissajousXmas.points[107].suppressPreviousTrack = false;

		lissajousXmas.points[108].x = 2374;
		lissajousXmas.points[108].y = 1067;
		lissajousXmas.points[108].suppressPreviousTrack = false;

		lissajousXmas.points[109].x = 2291;
		lissajousXmas.points[109].y = 1048;
		lissajousXmas.points[109].suppressPreviousTrack = false;

		lissajousXmas.points[110].x = 2176;
		lissajousXmas.points[110].y = 1048;
		lissajousXmas.points[110].suppressPreviousTrack = false;

		lissajousXmas.points[111].x = 2246;
		lissajousXmas.points[111].y = 421;
		lissajousXmas.points[111].suppressPreviousTrack = false;

		lissajousXmas.points[112].x = 1850;
		lissajousXmas.points[112].y = 427;
		lissajousXmas.points[112].suppressPreviousTrack = false;

		lissajousXmas.points[113].x = 1696;
		lissajousXmas.points[113].y = 1426;
		lissajousXmas.points[113].suppressPreviousTrack = true;

		lissajousXmas.points[114].x = 1709;
		lissajousXmas.points[114].y = 1496;
		lissajousXmas.points[114].suppressPreviousTrack = false;

		lissajousXmas.points[115].x = 1645;
		lissajousXmas.points[115].y = 1534;
		lissajousXmas.points[115].suppressPreviousTrack = false;

		lissajousXmas.points[116].x = 1722;
		lissajousXmas.points[116].y = 1541;
		lissajousXmas.points[116].suppressPreviousTrack = false;

		lissajousXmas.points[117].x = 1741;
		lissajousXmas.points[117].y = 1611;
		lissajousXmas.points[117].suppressPreviousTrack = false;

		lissajousXmas.points[118].x = 1766;
		lissajousXmas.points[118].y = 1554;
		lissajousXmas.points[118].suppressPreviousTrack = false;

		lissajousXmas.points[119].x = 1843;
		lissajousXmas.points[119].y = 1541;
		lissajousXmas.points[119].suppressPreviousTrack = false;

		lissajousXmas.points[120].x = 1786;
		lissajousXmas.points[120].y = 1483;
		lissajousXmas.points[120].suppressPreviousTrack = false;

		lissajousXmas.points[121].x = 1811;
		lissajousXmas.points[121].y = 1432;
		lissajousXmas.points[121].suppressPreviousTrack = false;

		lissajousXmas.points[122].x = 1747;
		lissajousXmas.points[122].y = 1464;
		lissajousXmas.points[122].suppressPreviousTrack = false;

		lissajousXmas.points[123].x = 1696;
		lissajousXmas.points[123].y = 1426;
		lissajousXmas.points[123].suppressPreviousTrack = false;

		lissajousXmas.points[124].x = 2112;
		lissajousXmas.points[124].y = 2078;
		lissajousXmas.points[124].suppressPreviousTrack = true;

		lissajousXmas.points[125].x = 2144;
		lissajousXmas.points[125].y = 2117;
		lissajousXmas.points[125].suppressPreviousTrack = false;

		lissajousXmas.points[126].x = 2099;
		lissajousXmas.points[126].y = 2123;
		lissajousXmas.points[126].suppressPreviousTrack = false;

		lissajousXmas.points[127].x = 2074;
		lissajousXmas.points[127].y = 2123;
		lissajousXmas.points[127].suppressPreviousTrack = false;

		lissajousXmas.points[128].x = 2150;
		lissajousXmas.points[128].y = 2155;
		lissajousXmas.points[128].suppressPreviousTrack = false;

		lissajousXmas.points[129].x = 2170;
		lissajousXmas.points[129].y = 2226;
		lissajousXmas.points[129].suppressPreviousTrack = false;

		lissajousXmas.points[130].x = 2214;
		lissajousXmas.points[130].y = 2149;
		lissajousXmas.points[130].suppressPreviousTrack = false;

		lissajousXmas.points[131].x = 2285;
		lissajousXmas.points[131].y = 2136;
		lissajousXmas.points[131].suppressPreviousTrack = false;

		lissajousXmas.points[132].x = 2214;
		lissajousXmas.points[132].y = 2104;
		lissajousXmas.points[132].suppressPreviousTrack = false;

		lissajousXmas.points[133].x = 2208;
		lissajousXmas.points[133].y = 2008;
		lissajousXmas.points[133].suppressPreviousTrack = false;

		lissajousXmas.points[134].x = 2170;
		lissajousXmas.points[134].y = 2104;
		lissajousXmas.points[134].suppressPreviousTrack = false;

		lissajousXmas.points[135].x = 2131;
		lissajousXmas.points[135].y = 2130;
		lissajousXmas.points[135].suppressPreviousTrack = false;		

		// Figuur afsluiten met kopie van eerste punt.
		lissajousXmas.points[136].x = 1850;
		lissajousXmas.points[136].y = 421;
		lissajousXmas.points[136].suppressPreviousTrack = true;

		// Aantal punten megeven.
		lissajousXmas.length = 137;
	}
	#endif
	
	#ifdef VIVES
	{
		lissajousXmas.points[0].x = 296;
		lissajousXmas.points[0].y = 1667;
		lissajousXmas.points[0].suppressPreviousTrack = false;

		lissajousXmas.points[1].x = 21;
		lissajousXmas.points[1].y = 2442;
		lissajousXmas.points[1].suppressPreviousTrack = false;

		lissajousXmas.points[2].x = 251;
		lissajousXmas.points[2].y = 2442;
		lissajousXmas.points[2].suppressPreviousTrack = false;

		lissajousXmas.points[3].x = 437;
		lissajousXmas.points[3].y = 1917;
		lissajousXmas.points[3].suppressPreviousTrack = false;

		lissajousXmas.points[4].x = 616;
		lissajousXmas.points[4].y = 2442;
		lissajousXmas.points[4].suppressPreviousTrack = false;

		lissajousXmas.points[5].x = 866;
		lissajousXmas.points[5].y = 2435;
		lissajousXmas.points[5].suppressPreviousTrack = false;

		lissajousXmas.points[6].x = 578;
		lissajousXmas.points[6].y = 1674;
		lissajousXmas.points[6].suppressPreviousTrack = false;

		lissajousXmas.points[7].x = 296;
		lissajousXmas.points[7].y = 1674;
		lissajousXmas.points[7].suppressPreviousTrack = false;

		lissajousXmas.points[8].x = 923;
		lissajousXmas.points[8].y = 1693;
		lissajousXmas.points[8].suppressPreviousTrack = true;

		lissajousXmas.points[9].x = 930;
		lissajousXmas.points[9].y = 2435;
		lissajousXmas.points[9].suppressPreviousTrack = false;

		lissajousXmas.points[10].x = 1154;
		lissajousXmas.points[10].y = 2442;
		lissajousXmas.points[10].suppressPreviousTrack = false;

		lissajousXmas.points[11].x = 1166;
		lissajousXmas.points[11].y = 1674;
		lissajousXmas.points[11].suppressPreviousTrack = false;

		lissajousXmas.points[12].x = 923;
		lissajousXmas.points[12].y = 1667;
		lissajousXmas.points[12].suppressPreviousTrack = false;

		lissajousXmas.points[13].x = 1499;
		lissajousXmas.points[13].y = 1667;
		lissajousXmas.points[13].suppressPreviousTrack = true;

		lissajousXmas.points[14].x = 1224;
		lissajousXmas.points[14].y = 2435;
		lissajousXmas.points[14].suppressPreviousTrack = false;

		lissajousXmas.points[15].x = 1474;
		lissajousXmas.points[15].y = 2442;
		lissajousXmas.points[15].suppressPreviousTrack = false;

		lissajousXmas.points[16].x = 1646;
		lissajousXmas.points[16].y = 1904;
		lissajousXmas.points[16].suppressPreviousTrack = false;

		lissajousXmas.points[17].x = 1813;
		lissajousXmas.points[17].y = 2435;
		lissajousXmas.points[17].suppressPreviousTrack = false;

		lissajousXmas.points[18].x = 2056;
		lissajousXmas.points[18].y = 2442;
		lissajousXmas.points[18].suppressPreviousTrack = false;

		lissajousXmas.points[19].x = 1800;
		lissajousXmas.points[19].y = 1680;
		lissajousXmas.points[19].suppressPreviousTrack = false;

		lissajousXmas.points[20].x = 1493;
		lissajousXmas.points[20].y = 1667;
		lissajousXmas.points[20].suppressPreviousTrack = false;

		lissajousXmas.points[21].x = 2843;
		lissajousXmas.points[21].y = 1923;
		lissajousXmas.points[21].suppressPreviousTrack = true;

		lissajousXmas.points[22].x = 2606;
		lissajousXmas.points[22].y = 1930;
		lissajousXmas.points[22].suppressPreviousTrack = false;

		lissajousXmas.points[23].x = 2587;
		lissajousXmas.points[23].y = 1917;
		lissajousXmas.points[23].suppressPreviousTrack = false;

		lissajousXmas.points[24].x = 2562;
		lissajousXmas.points[24].y = 1891;
		lissajousXmas.points[24].suppressPreviousTrack = false;

		lissajousXmas.points[25].x = 2510;
		lissajousXmas.points[25].y = 1866;
		lissajousXmas.points[25].suppressPreviousTrack = false;

		lissajousXmas.points[26].x = 2434;
		lissajousXmas.points[26].y = 1853;
		lissajousXmas.points[26].suppressPreviousTrack = false;

		lissajousXmas.points[27].x = 2382;
		lissajousXmas.points[27].y = 1872;
		lissajousXmas.points[27].suppressPreviousTrack = false;

		lissajousXmas.points[28].x = 2338;
		lissajousXmas.points[28].y = 1910;
		lissajousXmas.points[28].suppressPreviousTrack = false;

		lissajousXmas.points[29].x = 2318;
		lissajousXmas.points[29].y = 1942;
		lissajousXmas.points[29].suppressPreviousTrack = false;

		lissajousXmas.points[30].x = 2318;
		lissajousXmas.points[30].y = 1994;
		lissajousXmas.points[30].suppressPreviousTrack = false;

		lissajousXmas.points[31].x = 2862;
		lissajousXmas.points[31].y = 1994;
		lissajousXmas.points[31].suppressPreviousTrack = false;

		lissajousXmas.points[32].x = 2869;
		lissajousXmas.points[32].y = 2058;
		lissajousXmas.points[32].suppressPreviousTrack = false;

		lissajousXmas.points[33].x = 2869;
		lissajousXmas.points[33].y = 2109;
		lissajousXmas.points[33].suppressPreviousTrack = false;

		lissajousXmas.points[34].x = 2862;
		lissajousXmas.points[34].y = 2179;
		lissajousXmas.points[34].suppressPreviousTrack = false;

		lissajousXmas.points[35].x = 2830;
		lissajousXmas.points[35].y = 2243;
		lissajousXmas.points[35].suppressPreviousTrack = false;

		lissajousXmas.points[36].x = 2798;
		lissajousXmas.points[36].y = 2301;
		lissajousXmas.points[36].suppressPreviousTrack = false;

		lissajousXmas.points[37].x = 2734;
		lissajousXmas.points[37].y = 2358;
		lissajousXmas.points[37].suppressPreviousTrack = false;

		lissajousXmas.points[38].x = 2645;
		lissajousXmas.points[38].y = 2429;
		lissajousXmas.points[38].suppressPreviousTrack = false;

		lissajousXmas.points[39].x = 2555;
		lissajousXmas.points[39].y = 2448;
		lissajousXmas.points[39].suppressPreviousTrack = false;

		lissajousXmas.points[40].x = 2498;
		lissajousXmas.points[40].y = 2461;
		lissajousXmas.points[40].suppressPreviousTrack = false;

		lissajousXmas.points[41].x = 2395;
		lissajousXmas.points[41].y = 2461;
		lissajousXmas.points[41].suppressPreviousTrack = false;

		lissajousXmas.points[42].x = 2331;
		lissajousXmas.points[42].y = 2435;
		lissajousXmas.points[42].suppressPreviousTrack = false;

		lissajousXmas.points[43].x = 2261;
		lissajousXmas.points[43].y = 2403;
		lissajousXmas.points[43].suppressPreviousTrack = false;

		lissajousXmas.points[44].x = 2203;
		lissajousXmas.points[44].y = 2365;
		lissajousXmas.points[44].suppressPreviousTrack = false;

		lissajousXmas.points[45].x = 2152;
		lissajousXmas.points[45].y = 2314;
		lissajousXmas.points[45].suppressPreviousTrack = false;

		lissajousXmas.points[46].x = 2101;
		lissajousXmas.points[46].y = 2218;
		lissajousXmas.points[46].suppressPreviousTrack = false;

		lissajousXmas.points[47].x = 2082;
		lissajousXmas.points[47].y = 2122;
		lissajousXmas.points[47].suppressPreviousTrack = false;

		lissajousXmas.points[48].x = 2082;
		lissajousXmas.points[48].y = 2006;
		lissajousXmas.points[48].suppressPreviousTrack = false;

		lissajousXmas.points[49].x = 2114;
		lissajousXmas.points[49].y = 1878;
		lissajousXmas.points[49].suppressPreviousTrack = false;

		lissajousXmas.points[50].x = 2165;
		lissajousXmas.points[50].y = 1814;
		lissajousXmas.points[50].suppressPreviousTrack = false;

		lissajousXmas.points[51].x = 2229;
		lissajousXmas.points[51].y = 1763;
		lissajousXmas.points[51].suppressPreviousTrack = false;

		lissajousXmas.points[52].x = 2306;
		lissajousXmas.points[52].y = 1712;
		lissajousXmas.points[52].suppressPreviousTrack = false;

		lissajousXmas.points[53].x = 2389;
		lissajousXmas.points[53].y = 1680;
		lissajousXmas.points[53].suppressPreviousTrack = false;

		lissajousXmas.points[54].x = 2466;
		lissajousXmas.points[54].y = 1661;
		lissajousXmas.points[54].suppressPreviousTrack = false;

		lissajousXmas.points[55].x = 2555;
		lissajousXmas.points[55].y = 1661;
		lissajousXmas.points[55].suppressPreviousTrack = false;

		lissajousXmas.points[56].x = 2626;
		lissajousXmas.points[56].y = 1667;
		lissajousXmas.points[56].suppressPreviousTrack = false;

		lissajousXmas.points[57].x = 2709;
		lissajousXmas.points[57].y = 1712;
		lissajousXmas.points[57].suppressPreviousTrack = false;

		lissajousXmas.points[58].x = 2773;
		lissajousXmas.points[58].y = 1763;
		lissajousXmas.points[58].suppressPreviousTrack = false;

		lissajousXmas.points[59].x = 2824;
		lissajousXmas.points[59].y = 1859;
		lissajousXmas.points[59].suppressPreviousTrack = false;

		lissajousXmas.points[60].x = 2837;
		lissajousXmas.points[60].y = 1917;
		lissajousXmas.points[60].suppressPreviousTrack = false;

		lissajousXmas.points[61].x = 2626;
		lissajousXmas.points[61].y = 2147;
		lissajousXmas.points[61].suppressPreviousTrack = true;

		lissajousXmas.points[62].x = 2331;
		lissajousXmas.points[62].y = 2179;
		lissajousXmas.points[62].suppressPreviousTrack = false;

		lissajousXmas.points[63].x = 2350;
		lissajousXmas.points[63].y = 2224;
		lissajousXmas.points[63].suppressPreviousTrack = false;

		lissajousXmas.points[64].x = 2421;
		lissajousXmas.points[64].y = 2262;
		lissajousXmas.points[64].suppressPreviousTrack = false;

		lissajousXmas.points[65].x = 2485;
		lissajousXmas.points[65].y = 2262;
		lissajousXmas.points[65].suppressPreviousTrack = false;

		lissajousXmas.points[66].x = 2594;
		lissajousXmas.points[66].y = 2205;
		lissajousXmas.points[66].suppressPreviousTrack = false;

		lissajousXmas.points[67].x = 2606;
		lissajousXmas.points[67].y = 2166;
		lissajousXmas.points[67].suppressPreviousTrack = false;

		lissajousXmas.points[68].x = 2619;
		lissajousXmas.points[68].y = 2122;
		lissajousXmas.points[68].suppressPreviousTrack = false;

		lissajousXmas.points[69].x = 2907;
		lissajousXmas.points[69].y = 1923;
		lissajousXmas.points[69].suppressPreviousTrack = true;

		lissajousXmas.points[70].x = 3144;
		lissajousXmas.points[70].y = 1923;
		lissajousXmas.points[70].suppressPreviousTrack = false;

		lissajousXmas.points[71].x = 3163;
		lissajousXmas.points[71].y = 1878;
		lissajousXmas.points[71].suppressPreviousTrack = false;

		lissajousXmas.points[72].x = 3214;
		lissajousXmas.points[72].y = 1840;
		lissajousXmas.points[72].suppressPreviousTrack = false;

		lissajousXmas.points[73].x = 3272;
		lissajousXmas.points[73].y = 1834;
		lissajousXmas.points[73].suppressPreviousTrack = false;

		lissajousXmas.points[74].x = 3330;
		lissajousXmas.points[74].y = 1846;
		lissajousXmas.points[74].suppressPreviousTrack = false;

		lissajousXmas.points[75].x = 3368;
		lissajousXmas.points[75].y = 1891;
		lissajousXmas.points[75].suppressPreviousTrack = false;

		lissajousXmas.points[76].x = 3355;
		lissajousXmas.points[76].y = 1949;
		lissajousXmas.points[76].suppressPreviousTrack = false;

		lissajousXmas.points[77].x = 3310;
		lissajousXmas.points[77].y = 1968;
		lissajousXmas.points[77].suppressPreviousTrack = false;

		lissajousXmas.points[78].x = 3144;
		lissajousXmas.points[78].y = 2013;
		lissajousXmas.points[78].suppressPreviousTrack = false;

		lissajousXmas.points[79].x = 3048;
		lissajousXmas.points[79].y = 2038;
		lissajousXmas.points[79].suppressPreviousTrack = false;

		lissajousXmas.points[80].x = 2978;
		lissajousXmas.points[80].y = 2070;
		lissajousXmas.points[80].suppressPreviousTrack = false;

		lissajousXmas.points[81].x = 2926;
		lissajousXmas.points[81].y = 2179;
		lissajousXmas.points[81].suppressPreviousTrack = false;

		lissajousXmas.points[82].x = 2958;
		lissajousXmas.points[82].y = 2320;
		lissajousXmas.points[82].suppressPreviousTrack = false;

		lissajousXmas.points[83].x = 3010;
		lissajousXmas.points[83].y = 2384;
		lissajousXmas.points[83].suppressPreviousTrack = false;

		lissajousXmas.points[84].x = 3054;
		lissajousXmas.points[84].y = 2410;
		lissajousXmas.points[84].suppressPreviousTrack = false;

		lissajousXmas.points[85].x = 3125;
		lissajousXmas.points[85].y = 2435;
		lissajousXmas.points[85].suppressPreviousTrack = false;

		lissajousXmas.points[86].x = 3221;
		lissajousXmas.points[86].y = 2448;
		lissajousXmas.points[86].suppressPreviousTrack = false;

		lissajousXmas.points[87].x = 3291;
		lissajousXmas.points[87].y = 2448;
		lissajousXmas.points[87].suppressPreviousTrack = false;

		lissajousXmas.points[88].x = 3368;
		lissajousXmas.points[88].y = 2435;
		lissajousXmas.points[88].suppressPreviousTrack = false;

		lissajousXmas.points[89].x = 3426;
		lissajousXmas.points[89].y = 2422;
		lissajousXmas.points[89].suppressPreviousTrack = false;

		lissajousXmas.points[90].x = 3490;
		lissajousXmas.points[90].y = 2378;
		lissajousXmas.points[90].suppressPreviousTrack = false;

		lissajousXmas.points[91].x = 3515;
		lissajousXmas.points[91].y = 2339;
		lissajousXmas.points[91].suppressPreviousTrack = false;

		lissajousXmas.points[92].x = 3547;
		lissajousXmas.points[92].y = 2282;
		lissajousXmas.points[92].suppressPreviousTrack = false;

		lissajousXmas.points[93].x = 3573;
		lissajousXmas.points[93].y = 2211;
		lissajousXmas.points[93].suppressPreviousTrack = false;

		lissajousXmas.points[94].x = 3573;
		lissajousXmas.points[94].y = 2192;
		lissajousXmas.points[94].suppressPreviousTrack = false;

		lissajousXmas.points[95].x = 3368;
		lissajousXmas.points[95].y = 2173;
		lissajousXmas.points[95].suppressPreviousTrack = false;

		lissajousXmas.points[96].x = 3355;
		lissajousXmas.points[96].y = 2205;
		lissajousXmas.points[96].suppressPreviousTrack = false;

		lissajousXmas.points[97].x = 3317;
		lissajousXmas.points[97].y = 2256;
		lissajousXmas.points[97].suppressPreviousTrack = false;

		lissajousXmas.points[98].x = 3310;
		lissajousXmas.points[98].y = 2256;
		lissajousXmas.points[98].suppressPreviousTrack = false;

		lissajousXmas.points[99].x = 3253;
		lissajousXmas.points[99].y = 2275;
		lissajousXmas.points[99].suppressPreviousTrack = false;

		lissajousXmas.points[100].x = 3195;
		lissajousXmas.points[100].y = 2275;
		lissajousXmas.points[100].suppressPreviousTrack = false;

		lissajousXmas.points[101].x = 3170;
		lissajousXmas.points[101].y = 2243;
		lissajousXmas.points[101].suppressPreviousTrack = false;

		lissajousXmas.points[102].x = 3163;
		lissajousXmas.points[102].y = 2205;
		lissajousXmas.points[102].suppressPreviousTrack = false;

		lissajousXmas.points[103].x = 3195;
		lissajousXmas.points[103].y = 2173;
		lissajousXmas.points[103].suppressPreviousTrack = false;

		lissajousXmas.points[104].x = 3266;
		lissajousXmas.points[104].y = 2147;
		lissajousXmas.points[104].suppressPreviousTrack = false;

		lissajousXmas.points[105].x = 3374;
		lissajousXmas.points[105].y = 2115;
		lissajousXmas.points[105].suppressPreviousTrack = false;

		lissajousXmas.points[106].x = 3470;
		lissajousXmas.points[106].y = 2083;
		lissajousXmas.points[106].suppressPreviousTrack = false;

		lissajousXmas.points[107].x = 3522;
		lissajousXmas.points[107].y = 2051;
		lissajousXmas.points[107].suppressPreviousTrack = false;

		lissajousXmas.points[108].x = 3560;
		lissajousXmas.points[108].y = 1994;
		lissajousXmas.points[108].suppressPreviousTrack = false;

		lissajousXmas.points[109].x = 3586;
		lissajousXmas.points[109].y = 1917;
		lissajousXmas.points[109].suppressPreviousTrack = false;

		lissajousXmas.points[110].x = 3579;
		lissajousXmas.points[110].y = 1834;
		lissajousXmas.points[110].suppressPreviousTrack = false;

		lissajousXmas.points[111].x = 3528;
		lissajousXmas.points[111].y = 1744;
		lissajousXmas.points[111].suppressPreviousTrack = false;

		lissajousXmas.points[112].x = 3477;
		lissajousXmas.points[112].y = 1712;
		lissajousXmas.points[112].suppressPreviousTrack = false;

		lissajousXmas.points[113].x = 3394;
		lissajousXmas.points[113].y = 1680;
		lissajousXmas.points[113].suppressPreviousTrack = false;

		lissajousXmas.points[114].x = 3291;
		lissajousXmas.points[114].y = 1654;
		lissajousXmas.points[114].suppressPreviousTrack = false;

		lissajousXmas.points[115].x = 3214;
		lissajousXmas.points[115].y = 1654;
		lissajousXmas.points[115].suppressPreviousTrack = false;

		lissajousXmas.points[116].x = 3131;
		lissajousXmas.points[116].y = 1674;
		lissajousXmas.points[116].suppressPreviousTrack = false;

		lissajousXmas.points[117].x = 3067;
		lissajousXmas.points[117].y = 1706;
		lissajousXmas.points[117].suppressPreviousTrack = false;

		lissajousXmas.points[118].x = 3016;
		lissajousXmas.points[118].y = 1738;
		lissajousXmas.points[118].suppressPreviousTrack = false;

		lissajousXmas.points[119].x = 2952;
		lissajousXmas.points[119].y = 1814;
		lissajousXmas.points[119].suppressPreviousTrack = false;

		lissajousXmas.points[120].x = 2920;
		lissajousXmas.points[120].y = 1898;
		lissajousXmas.points[120].suppressPreviousTrack = false;

		// Figuur afsluiten met kopie van eerste punt.
		lissajousXmas.points[121].x = 296;
		lissajousXmas.points[121].y = 1667;
		lissajousXmas.points[121].suppressPreviousTrack = true;
		
		// Aantal punten megeven.
		lissajousXmas.length = 122;
	}
	#endif
	
	#ifdef RECTANGLE
	{
		lissajousRectangle.points[0].x = 674;
		lissajousRectangle.points[0].y = 862;
		lissajousRectangle.points[0].suppressPreviousTrack = false;
		lissajousRectangle.points[1].x = 629;
		lissajousRectangle.points[1].y = 2974;
		lissajousRectangle.points[1].suppressPreviousTrack = false;
		lissajousRectangle.points[2].x = 3150;
		lissajousRectangle.points[2].y = 2930;
		lissajousRectangle.points[2].suppressPreviousTrack = false;
		lissajousRectangle.points[3].x = 3138;
		lissajousRectangle.points[3].y = 798;
		lissajousRectangle.points[3].suppressPreviousTrack = false;
		
		
		// Figuur afsluiten met kopie van eerste punt.
		lissajousRectangle.points[4].x = 674;
		lissajousRectangle.points[4].y = 862;
		lissajousRectangle.points[4].suppressPreviousTrack = false;

		// Aantal punten megeven.
		lissajousRectangle.length = 5;
	}
	#endif
	
	#ifdef PEACE
	{
		// TODO: peace sign Lissajous maken...
		lissajousPeace.points[0].x = 674;
		lissajousPeace.points[0].y = 862;
		lissajousPeace.points[0].suppressPreviousTrack = false;
		lissajousPeace.points[1].x = 629;
		lissajousPeace.points[1].y = 2974;
		lissajousPeace.points[1].suppressPreviousTrack = false;
		lissajousPeace.points[2].x = 3150;
		lissajousPeace.points[2].y = 2930;
		lissajousPeace.points[2].suppressPreviousTrack = false;
		lissajousPeace.points[3].x = 3138;
		lissajousPeace.points[3].y = 798;
		lissajousPeace.points[3].suppressPreviousTrack = false;
		
		
		// Figuur afsluiten met kopie van eerste punt.
		lissajousPeace.points[4].x = 674;
		lissajousPeace.points[4].y = 862;
		lissajousPeace.points[4].suppressPreviousTrack = false;

		// Aantal punten megeven.
		lissajousPeace.length = 5;
	}
	#endif
	
	while (1)
	{	
		// Lissajous code.
		{
			#ifdef MEASURE_LOOP_TIME
				// Lustijd meten (optioneel).
				startTicks = ticks;
			#endif
			
			// Teken de volledige figuur... Duurt ongeveer 15ms voor de Kerstboom (vastgesteld via meting).
			if(!run)
				// Indien geen m&m wordt afgeleverd, toon de kerstboom.
				DrawLissajous(&lissajousXmas, lissajousXmas.length);		
			else
				// Indien een m&m wordt afgeleverd, toon het vredesteken.
				DrawLissajous(&lissajousPeace, lissajousPeace.length);
			
			#ifdef MEASURE_LOOP_TIME
				// Lustijd meten (optioneel).
				deltaTicks = ticks - startTicks;		
				sprintf(text, "Loop time: %d ms.\r\n", deltaTicks);
				StringToUsart2(text);
			#endif
		}
		
		// m&m code
		{
			// Flank gezien, lever één M&M af.
			if(SW1Active() && (sw1Help == false))
			{
				sw1Help = true;
				run = true;
			}
			if(!SW1Active())
				sw1Help = false;
			
			// De letter 'm' ontvangen via UART2, lever één m&m af.
			if((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
			{
				// Byte ontvangen, lees hem om alle vlaggen te wissen.
				if(USART2->RDR == 'm')
				{
					run = true;
				}
			}
				
			// 0 -> 4095
			adValue = GetAdValue();
			
			// 0 -> 100
			adValue /= AD_DIVIDER;		
			
			// Wannabe timer verhogen om detectie van een probleem te kunnen doen.
			wannabeTimer++;
			
			// Zolang nodig, draai.
			if((run) && (wannabeTimer < (ERROR_TIMEOUT/LOOP_DELAY)))
				SetPwm(SERVO_JUST_BELOW_MIDPOINT + adValue - SERVO_SPEED);
			else
			{
				SetPwm(SERVO_JUST_BELOW_MIDPOINT + adValue);
				wannabeTimer = 0;
				run = false;
			}
				
			// Vallende m&m gedetecteerd (flankdetectie)? Stop.
			if(IR1Active() && (IR1Help == false))
			{
				IR1Help = true;
				run = false;			
				count++;			
				ToggleLed(1);
				
				sprintf(text, "%d\r\n", count);
				StringToUsart2(text);
			}		
			if(!IR1Active())
				IR1Help = false;
		}
		
		// OPM: geen WaitForMs() nodig, de Lissajous code neemt 'voldoende' tijd...
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
