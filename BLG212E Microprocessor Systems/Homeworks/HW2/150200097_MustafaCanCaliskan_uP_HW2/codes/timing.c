#include "timing.h"

extern uint32_t	ticks;

void Systick_Start(void)
{
	ticks = 0;

	SysTick->LOAD = (SystemCoreClock / 100000) - 1; // 1us interval
	SysTick->VAL = 0U;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

uint32_t	Systick_Stop(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	uint32_t	elapsed = ticks; // 10s of us
	return (elapsed);
}
