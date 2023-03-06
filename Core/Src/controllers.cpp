/*
 * controllers.cpp
 *
 *  Created on: 5 Mar 2023
 *      Author: salavat.magazov
 */

#include "CHumidityController.h"
#include "CTemperatureController.h"

// Instantiate all classes
CTemperatureController g_temperature_controller(100,
                                                "temperature",
                                                4092,
                                                osPriorityNormal);

#ifdef __cplusplus
extern "C"
{
#endif

    void initialiseHardware() {}

    void startControllers()
    {
        g_temperature_controller.start();
    }

#ifdef __cplusplus
}
#endif
