
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"

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

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_usart;
    //here we are going to do the low level initialization of the USART2 peripheral
    // Enable the Required peripheral clock
	__HAL_RCC_USART2_CLK_ENABLE();
    //	2. Do pin muxing configurations
    gpio_usart.Pin = GPIO_PIN_2;      // TX Setting
    gpio_usart.Mode = GPIO_MODE_AF_PP;
    gpio_usart.Pull = GPIO_PULLUP;
    gpio_usart.Alternate = GPIO_AF7_USART2;
    gpio_usart.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_usart);
    //---------
    gpio_usart.Pin = GPIO_PIN_3;      //  RX Setting
    HAL_GPIO_Init(GPIOA, &gpio_usart);
	//	3. Enable the peripheral IRQ in the NVIC  (Optional)
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn, 15,0);

}