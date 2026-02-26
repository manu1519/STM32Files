
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
    // Low Level processor specific inits
        // 1. Set up the priority goruping of the arm Cortex MX processor
        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

        // 2. Enable the required system exceptions of the arm Cortex Mx Processor
        SCB -> SHCSR = 0x7 << 16; //usage faul, memory fault and bus fault system exception

        // 3. Configure the priority for the system exceptions
        HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
        HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
        HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);

}