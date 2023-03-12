/*
 * CTemperatureController.h
 *
 *  Created on: 6 Mar 2023
 *      Author: salavat.magazov
 */

#ifndef CTEMPERATURECONTROLLER_H_
#define CTEMPERATURECONTROLLER_H_

#include <CController.h>
#include <FreeRTOS_CLI.h>
#include <IHardwareMap.h>
#include <freertos_os2.h>
#include "CPIDLoop.h"
#include "CThermistor.h"

// TODO: consider making these classes singletons.

class CTemperatureController : public CController
{
public:
    CTemperatureController(uint32_t run_period,
                           const etl::string<configMAX_TASK_NAME_LEN> name,
                           uint32_t stack_depth,
                           osPriority_t priority);
    virtual ~CTemperatureController();

    virtual void run();

    static BaseType_t requestTemperature(char *pcWriteBuffer,
                                         size_t xWriteBufferLen,
                                         const char *pcCommandString);
    static constexpr uint8_t CHANNEL_COUNT =
        IHardwareMap::ADC_THEMISTOR_CHANNELS;
//    static constexpr float CALIB_COEFF[] = {-5.16917E-13,
//                                            1.70585E-09,
//                                            5.82242E-06,
//                                            -0.059851305,
//                                            180.289278};

private:
    float m_target[CHANNEL_COUNT];
    CThermistor m_sensor[CHANNEL_COUNT];
    CPIDLoop m_control[CHANNEL_COUNT];
};

#endif /* CTEMPERATURECONTROLLER_H_ */
