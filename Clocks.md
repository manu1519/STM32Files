#### System Clock (SYSCLK)
Those can drive the system clock:
- HSI Oscillator clock  has more errors
- HSE oscillator clock  It has less errors
- 2 Main PLL (PLL) Clocks

Normally devices has 2 following secondary clock sources
- 32 kHz loq-speed internal RC (LSI RC) drives independent watchdog and RTC for Auto-wakeup from Stop/standby mode
- 32.768 kHz low-speed external crystal (LSE crystal) optionally drives the RTCclock (RTCCLK) this is also more precisely than LSI/LSE

### NUCLEO-F446RE 
- HSI  -> 16 MHz **(Internal to MCU)** 
- HSE  -> 8MHz **(External to MCU)**
- PLL  -> Can generate clock up to 180MHz **(Internal to MCU)**
- LSI  -> 32 kHz **(Internal to MCU)**
- LSE  -> 32.768kHz **(External to MCU)**

#### Status of the Clocks (by default)
Consider each of them can be modified to optimize power consumption
- HSI  -> ***ON*** 
- HSE  -> ***OFF***
- PLL  -> ***OFF***
- LSI  -> ***OFF***
- LSE  -> ***OFF***

## HSI
- From a **Reset** or **Start-up** always is set as System Clock
- This is a source at low cost
- Has faster startup time than HSE
- Even with calibration the accuracy is not properly even is less than an external or ceramic resonator
- It can be used as backup by any fail
[[stm32f446re.pdf#page=105&offset=67,754|stm32f446re, 6.3.10 Internal clock source characteristics]]

#RCC Reset and Clock Control
## Methods to configure the SYSCLK Source
1. Enable the clock and wait until is ready. Try to focus only in the needed one
2. Initializes the CPU, AHB and APB busses clock prescalers. ***Don't cross max limit***
3. Configure the Flash latency by referencing to MCU RM
4. Select newly enabled Clock

#### APIs
- HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct)  (Full manage the steps 1)
- HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, unit32_t FLatency) (Full manage the steps 2-4)

## EXCERCISE
Using HSE Configure the SYSCLK as 8MHz
- AHB clock as 4MHz (HCLK)
- APB1 clock as 2 MHz (PCLK1)
- APB2 clock as 2 MHz (PCLK2)

1. [[rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf#page=116&offset=67,755|rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics, 6 Reset and clock control (RCC)]] This is the design of the STM32, Nevertheless, consider to open the STM32CubeIDE to look closely the actual values and settings of your board
2. Find the Notes from scripts on your code for the APIs
	- HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct)  (stm32f4xx_hal_rcc_ex.c)- HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, unit32_t FLatency) (stm32f4xx_hal_rcc.c)
3. Modify the main.c Consider the APIs needs to have a Variable, which must be defined
4. To set correctly those variables is prior to review the documentation through the APIs commands:
	- RCC_OscInitTypeDef  -> stm32f4xx_hal_rcc.h  (Look at the description and follow to get the properties and values) 
	- RCC_ClkInitTypeDef  -> stm32f4xx_hal_rcc.h  (Look at the description and follow to get the properties and values)
5. Following the diagrams from the STM32F4xx seems there is no external appliance of the Clock here, so in order to set the HSE it is necessary to consider the External Microcontroler which is using indeed the HSE
   [[mb1136-default-c04_schematic.pdf#page=1|mb1136-default-c04_schematic, Schematic Prints("All Documents",Logical)]]
6. 
