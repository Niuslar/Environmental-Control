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
#include <freertos_os2.h>

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

private:
};

#endif /* CTEMPERATURECONTROLLER_H_ */
