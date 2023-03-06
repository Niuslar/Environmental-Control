/*
 * CHumidityController.h
 *
 *  Created on: Mar 6, 2023
 *      Author: salavat.magazov
 */

#ifndef CHUMIDITYCONTROLLER_H_
#define CHUMIDITYCONTROLLER_H_

#include <CController.h>
#include <FreeRTOS_CLI.h>
#include <freertos_os2.h>

class CHumidityController : public CController
{
public:
    CHumidityController(uint32_t run_period,
                        const etl::string<configMAX_TASK_NAME_LEN> name,
                        uint32_t stack_depth,
                        osPriority_t priority);

    virtual ~CHumidityController();

    virtual void run();

    static BaseType_t requestHumidity(char *pcWriteBuffer,
                                      size_t xWriteBufferLen,
                                      const char *pcCommandString);
};

#endif /* CHUMIDITYCONTROLLER_H_ */
