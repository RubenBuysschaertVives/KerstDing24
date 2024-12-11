#include "stm32f091xc.h"

#if !defined(DAC_DEFINED)
	#define DAC_DEFINED
	// PA4 is DAC OUT 1.
	// PA5 is DAC OUT 2.
	// Let op: bij een Nucleo-bord is PA5 verbonden met de on board LED... Verwijden SB21 indien gewenst.
	
	void InitDAC(void);
	void SetDacX(uint16_t dacValue);
	void SetDacY(uint16_t dacValue);
	#endif
