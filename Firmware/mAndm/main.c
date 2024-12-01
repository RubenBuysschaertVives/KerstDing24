// Includes.
#include "stm32f091xc.h"
#include "stdio.h"
#include "stdbool.h"
#include "leds.h"
#include "buttons.h"
#include "usart2.h"
#include "ad.h"
#include "pwm.h"
#include "ir.h"

// Defines
#define SERVO_JUST_BELOW_MIDPOINT 1450			// Normaal middelpunt is 1500/2000. Doe daar een kleinigheid af zodat je later kan bijregelen met de on board potentiometer.
#define SERVO_SPEED	75											// Snelheid van de servo instellen (in 2000-sten).
#define AD_DIVIDER 40												// 12-bit AD-waarde herschalen.
#define LOOP_DELAY 10												// Hoofdlus niet sneller dan iedere 10ms doorlopen.
#define ERROR_TIMEOUT 9000									// Na 9 seconden geen m&m, stop sowieso.

// Functie prototypes.
void SystemClock_Config(void);
void InitIo(void);
void WaitForMs(uint32_t timespan);

// Variabelen aanmaken.
static bool IR1Help = false, run = false, sw1Help = false;
static uint16_t count = 0, wannabeTimer = 0;
static uint16_t adValue = 0;
static char text[101];
static volatile uint32_t ticks = 0;

// Entry point.
int main(void)
{
	// Initialisaties.
	SystemClock_Config();
	InitIo();
	InitButtons();
	InitLeds();
	InitUsart2(115200);
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
	
	// Laten weten dat we opgestart zijn, via de USART2 (USB).
	StringToUsart2("Reboot\r\n");
	
	// Oneindige lus starten.
	while (1)
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
		
		// Anti-dender.
		WaitForMs(LOOP_DELAY);
	}
	
	// Terugkeren zonder fouten... (unreachable).
	return 0;
}

// Functie om extra IO's te initialiseren.
void InitIo(void)
{

}

// Handler die iedere 1ms afloopt. Ingesteld met SystemCoreClockUpdate() en SysTick_Config().
void SysTick_Handler(void)
{
	ticks++;
}

// Wachtfunctie via de SysTick.
void WaitForMs(uint32_t timespan)
{
	uint32_t startTime = ticks;
	
	while(ticks < startTime + timespan);
}

// Klokken instellen. Deze functie niet wijzigen, tenzij je goed weet wat je doet.
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
