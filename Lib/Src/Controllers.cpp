/*
 * controllers.cpp
 *
 *  Created on: 5 Mar 2023
 *      Author: salavat.magazov
 */

#include "CLedsController.h"
#include "CTemperatureController.h"
#include "CUartCom.h"
#include "main.h"

// Instantiate all classes
CTemperatureController g_temperature_controller(100,
                                                "temperature",
                                                4092, // TODO: Check if CMSIS uses words or bytes
                                                2);

CLedsController g_leds_controller(50,
								  "leds",
								  100,
								  0);

CUartCom g_main_coms("main");
CUartCom g_debug_coms("debug");

#ifdef __cplusplus
extern "C"
{
#endif

    void initialiseHardware()
    {
    }

    void startControllers()
    {
        g_temperature_controller.start();
        g_leds_controller.start();
    }

#ifdef __cplusplus
}
#endif
