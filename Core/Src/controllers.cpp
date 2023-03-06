/*
 * controllers.cpp
 *
 *  Created on: 5 Mar 2023
 *      Author: salavat.magazov
 */

#include "CCO2Controller.h"
#include "CHumidityController.h"
#include "CTemperatureController.h"

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

#ifdef __cplusplus
extern "C"
{
#endif

    void initialiseHardware() {}

    void startControllers()
    {
        g_temperature_controller.start();
        g_humidity_controller.start();
        g_co2_controller.start();
    }

#ifdef __cplusplus
}
#endif
