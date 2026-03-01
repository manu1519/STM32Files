1. Open STM32CubeMx in order to get the configurations of the Board. Remember:
	1. Use File Tab to create a new project
	2. Use the Board Selector tab in order to find the Board, (Use the NUCLEO-F446RE for this specific case)
	3. **IMPORTANT** Always until anything is mentioned, START By DEFAULT the PINS 
	4. Then proceed to generate the Code, but first select **Project Manager** to configure correctly The Project Name, the Path and **IMPORTANT** Toolchain/IDE
	5. As this full implementation is using the VSCode Scope, use the CMake to get the code.
	6. Also remember to confirm the Code Generator to "Copy only the Necessary library files"
2. Creating the Files
	1. When it is applied a combination of VSCode with Eclipse and the compilers (CMake) always is gonna be a deeply problem between debug, compiler proceedure
	2. Take care of the Files created by the STM32Cube, do a different folder of this implementation
	3. **IMPORTANT** To run this into VSCode you should be aware of the CMakeLists.txt file, as this file is the one whom can re-route to your personalize files. Consider this specific functions
```
	   # Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE

    # Add user sources here
    ManuFiles/main.c
    ManuFiles/it.c
    ManuFiles/msp.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ManuFiles
    cmake/stm32cubemx/include
)
```

3. Applying Low Level Processor
	1. To applying this it is necessary to edit the msp.c file
	2. Here are some rules:
	   // Low Level processor specific inits
        // 1. Set up the priority goruping of the arm Cortex MX processor
        // 2. Enable the required system exceptions of the arm Cortex Mx Processor
        // 3. Configure the priority for the system exceptions
	3. To get the correctly APIs of the Cortex follow the Drivers/Src/stm32f4xx_hal_cortex.c
	4. By default on this Microcontroller, if there is not setting on the NVIC_PRIORITYGROUOP it takes the 0-***4*** 
	5. Consider this prior should determine when it has 2 pending actions and will move forward depending on their set values:
	   0 - 4 bits for preemption priority (Using this will attempt with the least priority)
	   4 - 0 bits for subpriority
	6. Considering the Exceptions, you can follow the Cortex manual [[pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=235&offset=67,754|pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics, 4.4.9 System handler control and state register (SHCSR)]]

4. Peripheral Initializations : UART2
	1. There are 2 types of Initialization, High Level or Low Level, 
		1. High Level are more related with the Bus appliances
		2. Low Level, is more related to Pin settings pin muxing, Clock, IRQ, NVIC 
	2. Will need to set a function were it calls the Pin related, this is following the ***stm32f446xx.h*** It is prior to read all the instructions per variable set. As this moments it is implemented the UART port, i should follow the parameters of the Peripheral ***huart2*** (High Level)
	3. To enable the Low Level initialization, Follow:
		1. Enable the Required peripheral clock
		2. Do pin muxing configurations
		3. Enable the peripheral IRQ in the NVIC
		4. Set the priority as per your application need
	4. **Normally when a peripheral is not working as expected the function HAL_UART_MspInit() is the first should be reviewed.***
	5. Pin Muxing vary depending on the Microcontroler, so it is MAINLY UNDERSTAND this step 
		1. UART needs RX and TX
		2. We can use 2 GPIOs of the MCU for RX and TX
		3. Before using GPIOs for UART is need to set their mode as: **ALTERNATE FUNCTIONALITY MODE**
		4. Which for this case the FUNCIONALITY MODE is the UART
		5. So to understand the Pins, we need to refer to the datasheet of the MCU [[stm32f446re.pdf#page=57&selection=154,0,207,1|stm32f446re, page 57]] and [[stm32f446re.pdf#page=60&selection=187,0,240,1|stm32f446re, page 60]] 
		6. To find the functions, refer to the stm32f4xx_hal_gpio.c Normally is used the *Init*
		7. [[[UART_FRAME.jpeg]]] ALWAYS SET to PullUp
		8. Part of the settings of Pins Mux, need to be careful with the Alternate set, as referred on [[stm32f446re.pdf#page=60&selection=187,0,240,1|stm32f446re, page 60]] When you select the pins there is a Column which describes the utilization in this case as it is USART2_RX and USART_TX the responsive setting should be AF7 (Pin PA2 and PA3) Also it will be necessary to find the Macros configurations in a different file than: *stm32f4xx_hal_gpio.c* this is: stm32f4xx_hal_gpio_ex.c
	6. The peripheral IRQ normally is used to set the Async communication which can result in: End Transmission, End Reception, Error Detection 
		1. To find which to use, it will needed to search on documentation stm32f446xx.h the function **IRQn_Type** 