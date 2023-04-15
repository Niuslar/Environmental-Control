/*
 * controllers.cpp
 *
 *  Created on: 5 Mar 2023
 *      Author: salavat.magazov
 */

#include "CTemperatureController.h"
#include "CUartCom.h"
#include "main.h"

// Instantiate all classes
CTemperatureController g_temperature_controller(100,
                                                "temperature",
                                                4092,
                                                2);

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
    }

#ifdef __cplusplus
}
#endif
