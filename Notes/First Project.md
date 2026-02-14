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