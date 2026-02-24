
#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
    // Low Level processor specific inits
        // 1. Set up the priority goruping of the arm Cortex MX processor
        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

        // 2. Enable the required system exceptions of the arm Cortex Mx Processor
        

        // 3. Configure the priority for the system exceptions

}