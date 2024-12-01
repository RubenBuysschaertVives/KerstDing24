#include "stm32f091xc.h"
#include "stdbool.h"
#include "buttons.h"

// IR-sluizen als input initialiseren.
void InitIRs(void)
{	
	// Clock voor GPIOB inschakelen.
	RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOBEN;	
	
	// Alle pinnen met IR-transistor verbonden, op input zetten.
	GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODER13;
}

bool IR1Active(void)
{
	// IR1 (aan begin glijbaan) actief?
	// Indien licht geblokkeerd => er passeert een m&m...
	// Dus actief hoge sensor als het ware.
	if((GPIOB->IDR & GPIO_IDR_13) == GPIO_IDR_13)
			return true;
	else
			return false;
}
