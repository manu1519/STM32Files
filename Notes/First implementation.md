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
        