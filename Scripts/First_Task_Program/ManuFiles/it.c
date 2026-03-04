#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_it.h"


void SysTick_Handler(void){
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}