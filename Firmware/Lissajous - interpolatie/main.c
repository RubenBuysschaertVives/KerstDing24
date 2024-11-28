// Kies een afbeelding.
#define KERSTBOOM
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
uint16_t i = 0;
volatile uint32_t ticks = 0;
char text[101];
Lissajous lissajous;

// Entry point.
int main(void)
{
	// Initialisaties.
	SystemClock_Config();
	InitUsart2(9600);
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
	#if defined(KERSTBOOM)
	{
		lissajous.points[0].x = 1843;
		lissajous.points[0].y = 427;
		lissajous.points[0].suppressPreviousTrack = false;

		lissajous.points[1].x = 1920;
		lissajous.points[1].y = 1010;
		lissajous.points[1].suppressPreviousTrack = false;

		lissajous.points[2].x = 1818;
		lissajous.points[2].y = 984;
		lissajous.points[2].suppressPreviousTrack = false;

		lissajous.points[3].x = 1651;
		lissajous.points[3].y = 965;
		lissajous.points[3].suppressPreviousTrack = false;

		lissajous.points[4].x = 1446;
		lissajous.points[4].y = 965;
		lissajous.points[4].suppressPreviousTrack = false;

		lissajous.points[5].x = 1254;
		lissajous.points[5].y = 965;
		lissajous.points[5].suppressPreviousTrack = false;

		lissajous.points[6].x = 1030;
		lissajous.points[6].y = 990;
		lissajous.points[6].suppressPreviousTrack = false;

		lissajous.points[7].x = 960;
		lissajous.points[7].y = 997;
		lissajous.points[7].suppressPreviousTrack = false;

		lissajous.points[8].x = 1088;
		lissajous.points[8].y = 1144;
		lissajous.points[8].suppressPreviousTrack = false;

		lissajous.points[9].x = 1261;
		lissajous.points[9].y = 1336;
		lissajous.points[9].suppressPreviousTrack = false;

		lissajous.points[10].x = 1459;
		lissajous.points[10].y = 1566;
		lissajous.points[10].suppressPreviousTrack = false;

		lissajous.points[11].x = 1600;
		lissajous.points[11].y = 1752;
		lissajous.points[11].suppressPreviousTrack = false;

		lissajous.points[12].x = 1651;
		lissajous.points[12].y = 1886;
		lissajous.points[12].suppressPreviousTrack = false;

		lissajous.points[13].x = 1459;
		lissajous.points[13].y = 1886;
		lissajous.points[13].suppressPreviousTrack = false;

		lissajous.points[14].x = 1555;
		lissajous.points[14].y = 2027;
		lissajous.points[14].suppressPreviousTrack = false;

		lissajous.points[15].x = 1658;
		lissajous.points[15].y = 2187;
		lissajous.points[15].suppressPreviousTrack = false;

		lissajous.points[16].x = 1766;
		lissajous.points[16].y = 2328;
		lissajous.points[16].suppressPreviousTrack = false;

		lissajous.points[17].x = 1843;
		lissajous.points[17].y = 2520;
		lissajous.points[17].suppressPreviousTrack = false;

		lissajous.points[18].x = 1722;
		lissajous.points[18].y = 2520;
		lissajous.points[18].suppressPreviousTrack = false;

		lissajous.points[19].x = 1773;
		lissajous.points[19].y = 2642;
		lissajous.points[19].suppressPreviousTrack = false;

		lissajous.points[20].x = 1888;
		lissajous.points[20].y = 2859;
		lissajous.points[20].suppressPreviousTrack = false;

		lissajous.points[21].x = 2054;
		lissajous.points[21].y = 3250;
		lissajous.points[21].suppressPreviousTrack = false;

		lissajous.points[22].x = 2042;
		lissajous.points[22].y = 3352;
		lissajous.points[22].suppressPreviousTrack = true;

		lissajous.points[23].x = 1914;
		lissajous.points[23].y = 3269;
		lissajous.points[23].suppressPreviousTrack = false;

		lissajous.points[24].x = 1965;
		lissajous.points[24].y = 3410;
		lissajous.points[24].suppressPreviousTrack = false;

		lissajous.points[25].x = 1837;
		lissajous.points[25].y = 3518;
		lissajous.points[25].suppressPreviousTrack = false;

		lissajous.points[26].x = 1990;
		lissajous.points[26].y = 3512;
		lissajous.points[26].suppressPreviousTrack = false;

		lissajous.points[27].x = 2042;
		lissajous.points[27].y = 3678;
		lissajous.points[27].suppressPreviousTrack = false;

		lissajous.points[28].x = 2086;
		lissajous.points[28].y = 3512;
		lissajous.points[28].suppressPreviousTrack = false;

		lissajous.points[29].x = 2259;
		lissajous.points[29].y = 3518;
		lissajous.points[29].suppressPreviousTrack = false;

		lissajous.points[30].x = 2131;
		lissajous.points[30].y = 3403;
		lissajous.points[30].suppressPreviousTrack = false;

		lissajous.points[31].x = 2182;
		lissajous.points[31].y = 3256;
		lissajous.points[31].suppressPreviousTrack = false;

		lissajous.points[32].x = 2042;
		lissajous.points[32].y = 3358;
		lissajous.points[32].suppressPreviousTrack = false;

		lissajous.points[33].x = 2042;
		lissajous.points[33].y = 3256;
		lissajous.points[33].suppressPreviousTrack = true;

		lissajous.points[34].x = 2099;
		lissajous.points[34].y = 3102;
		lissajous.points[34].suppressPreviousTrack = false;

		lissajous.points[35].x = 2189;
		lissajous.points[35].y = 2898;
		lissajous.points[35].suppressPreviousTrack = false;

		lissajous.points[36].x = 2272;
		lissajous.points[36].y = 2718;
		lissajous.points[36].suppressPreviousTrack = false;

		lissajous.points[37].x = 2381;
		lissajous.points[37].y = 2526;
		lissajous.points[37].suppressPreviousTrack = false;

		lissajous.points[38].x = 2394;
		lissajous.points[38].y = 2494;
		lissajous.points[38].suppressPreviousTrack = false;

		lissajous.points[39].x = 2246;
		lissajous.points[39].y = 2507;
		lissajous.points[39].suppressPreviousTrack = false;

		lissajous.points[40].x = 2298;
		lissajous.points[40].y = 2405;
		lissajous.points[40].suppressPreviousTrack = false;

		lissajous.points[41].x = 2362;
		lissajous.points[41].y = 2251;
		lissajous.points[41].suppressPreviousTrack = false;

		lissajous.points[42].x = 2445;
		lissajous.points[42].y = 2142;
		lissajous.points[42].suppressPreviousTrack = false;

		lissajous.points[43].x = 2547;
		lissajous.points[43].y = 2008;
		lissajous.points[43].suppressPreviousTrack = false;

		lissajous.points[44].x = 2682;
		lissajous.points[44].y = 1861;
		lissajous.points[44].suppressPreviousTrack = false;

		lissajous.points[45].x = 2451;
		lissajous.points[45].y = 1854;
		lissajous.points[45].suppressPreviousTrack = false;

		lissajous.points[46].x = 2477;
		lissajous.points[46].y = 1790;
		lissajous.points[46].suppressPreviousTrack = false;

		lissajous.points[47].x = 2618;
		lissajous.points[47].y = 1605;
		lissajous.points[47].suppressPreviousTrack = false;

		lissajous.points[48].x = 2758;
		lissajous.points[48].y = 1432;
		lissajous.points[48].suppressPreviousTrack = false;

		lissajous.points[49].x = 2944;
		lissajous.points[49].y = 1221;
		lissajous.points[49].suppressPreviousTrack = false;

		lissajous.points[50].x = 3091;
		lissajous.points[50].y = 1067;
		lissajous.points[50].suppressPreviousTrack = false;

		lissajous.points[51].x = 3149;
		lissajous.points[51].y = 1016;
		lissajous.points[51].suppressPreviousTrack = false;

		lissajous.points[52].x = 3194;
		lissajous.points[52].y = 971;
		lissajous.points[52].suppressPreviousTrack = false;

		lissajous.points[53].x = 2944;
		lissajous.points[53].y = 990;
		lissajous.points[53].suppressPreviousTrack = false;

		lissajous.points[54].x = 2758;
		lissajous.points[54].y = 1035;
		lissajous.points[54].suppressPreviousTrack = false;

		lissajous.points[55].x = 2541;
		lissajous.points[55].y = 1061;
		lissajous.points[55].suppressPreviousTrack = false;

		lissajous.points[56].x = 2374;
		lissajous.points[56].y = 1061;
		lissajous.points[56].suppressPreviousTrack = false;

		lissajous.points[57].x = 2310;
		lissajous.points[57].y = 1054;
		lissajous.points[57].suppressPreviousTrack = false;

		lissajous.points[58].x = 2176;
		lissajous.points[58].y = 1061;
		lissajous.points[58].suppressPreviousTrack = false;

		lissajous.points[59].x = 2259;
		lissajous.points[59].y = 427;
		lissajous.points[59].suppressPreviousTrack = false;

		lissajous.points[60].x = 1843;
		lissajous.points[60].y = 414;
		lissajous.points[60].suppressPreviousTrack = false;
		

		// Figuur afsluiten met kopie van eerste punt.
		lissajous.points[61].x = 1843;
		lissajous.points[61].y = 427;
		lissajous.points[61].suppressPreviousTrack = false;

		// Aantal punten megeven.
		lissajous.length = 62;
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
		// Teken de volledige figuur...
		DrawLissajous(&lissajous, lissajous.length);		
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
