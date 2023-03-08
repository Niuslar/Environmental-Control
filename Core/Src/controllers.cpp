/*
 * controllers.cpp
 *
 *  Created on: 5 Mar 2023
 *      Author: salavat.magazov
 */

#include "CCO2Controller.h"
#include "CCommandController.h"
#include "CHumidityController.h"
#include "CTemperatureController.h"
#include "CUartCom.h"
#include "main.h"

// Instantiate all classes
CTemperatureController g_temperature_controller(100,
                                                "temperature",
                                                4092,
                                                osPriorityNormal);
CHumidityController g_humidity_controller(100,
                                          "humidity",
                                          4092,
                                          osPriorityNormal);
CCO2Controller g_co2_controller(100, "co2", 4092, osPriorityNormal);

CCommandController g_command_controller("command", 4092, osPriorityAboveNormal);

CUartCom g_main_coms("main");
CUartCom g_debug_coms("debug");

#ifdef __cplusplus
extern "C"
{
#endif

    void initialiseHardware()
    {
        g_main_coms.init(&huart1, USART1_DE_GPIO_Port, USART1_DE_Pin);
        g_debug_coms.init(&huart2);
        g_command_controller.registerComChannel(&g_main_coms);
        g_command_controller.registerComChannel(&g_debug_coms);
        // TODO: the IComChannel needs to be told which task to notify.
    }

    void startControllers()
    {
        g_temperature_controller.start();
        g_humidity_controller.start();
        g_co2_controller.start();
        g_command_controller.start();
    }

#ifdef __cplusplus
}
#endif
