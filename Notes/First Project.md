#### Mostly differences between course Version to 2026 updates
1. STM32CubeMX is already changed the versions of Toolchain / IDE
   Was recommended to use CMake to avoid the Eclipse full files
2. Version: STM32Cube FW_F4 V1.28.3 is the selected as the most recently Firmware
3. Was added all necessary files
4. The purpose is not to configure any peripheral is only to get the creation and all driver files
5. This was a complete Mess

#### Important Notes
- VSCode it is not compatible with all resources of the STM32 
- Following the insights of the Gemini to solve the problems the most remarkable is the files integrations
- STM32CubeMX Programmer when it is download, this is not fully files download, which remains on the Resources
- It is recommended to use the Extension of the VSCode of STM32, however consider:
	- To Give a test and communicate with the board it must have:
	- Debug: STM32 Native
	- json of VSCode:
{

    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug STM32 (Oficial)",
            "type": "cortex-debug",
            "request": "launch",
            "servertype": "stlink",
            "interface": "swd",
            "serverArgs": ["-f", "interface/stlink.cfg"],
            "executable": "${command:cmake.launchTargetPath}",
            "liveWatch": {
                "enabled": true
            },
            "armToolchainPath": "C:/Users/Manuel/Downloads/arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-arm-none-eabi/bin",
            "serverpath": "C:/Users/Manuel/STMicroelectronics/STM32CubeProgrammer/bin/ST-LINK_gdbserver.exe"
        },
        {
            "showDevDebugOutput": "parsed",
            "cwd": "${workspaceRoot}",
            "executable": "./build/debug/Testing.elf",
            "name": "Debug STM32",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            "preLaunchTask": "Build STM",
            "device": "stm32f446",
            "configFiles": [
                "openocd.cfg"
            ]
        },
        {
            "showDevDebugOutput": "parsed",
            "cwd": "${workspaceRoot}",
            "executable": "./build/debug/Testing.elf",
            "name": "Attach STM32",
            "request": "attach",
            "type": "cortex-debug",
            "servertype": "openocd",
            "preLaunchTask": "Build STM",
            "device": "stm32f446",
            "configFiles": [
                "openocd.cfg"
            ]
        }
    ]
    }

- The tools of VSCode has visualization of:
	- Variables
	- Pila de llamadas (Muestra los cambiós en código)
	- Cortex Live Watch (Muestra ejecución y cambios de variables pero es necesario determinar cuales)
	- Las acciones se observan en Consola de Depuración


## Continuation with project
- The board STM32F446RE is using a Cortex-M4
- To deliver a message to the Serial Port, it was faced another issue:
	- The ST Extension from VSCode works more at superior level, rather than Board level
	- The mentioned above is translate as even with all well setting on the Board and communication with VSCode, there still configurations that it must to be aware from VSCode implementation
	- Serial Monitoring is using COM8(STMicrocontroler) 115200
- # EXTREMELY IMPORTANT
	- All implementations comes from "Application code and other source files" - "STM32-CUBE Layer (STM32Fx_HAL_DRIVER)" - "CMSIS-CORE" - "ARM Cortex Mx Processor"  ![[Architect.jpeg]]
	- So all API Calls **CANNOT** being writing as follow:
	    HAL_UART_Transmit(&huart2, (uint8_t*)user_data, strlen(user_data), HAL_MAX_DELAY);
	- And completely not follow to use APIs to communicate the Peripherals

#### Mandatory and Optional MCU Units
- Flash Controller Inits 
- Floating  point unit inits if supported (Optional)
- Stting up Stack (Mandatory)
- System Clock settings (optional) - HSI -HSE -System PLL
- Flash wait state settings when sysetem clock is more (Mandatory)
- Systick Timer initialization to trigger interrupt for every 1 ms (Required when use STM32 HAL APIs)

  `/* Reset of all peripherals, Initializes the Flash interface and the Systick. */`
  `HAL_Init();`
  `/* USER CODE BEGIN Init */
  
  `/* USER CODE END Init */`
  
  `/* Configure the system clock */`
  `SystemClock_Config();`

  `/* USER CODE BEGIN SysInit */`

  `/* USER CODE END SysInit */`

  `/* Initialize all configured peripherals */`
  `MX_GPIO_Init();`
  `MX_USART2_UART_Init();`

- The observed above is the code section that must initialize the APIs, those are related with the Clock 
  ![[ProgramFlow.jpeg]]