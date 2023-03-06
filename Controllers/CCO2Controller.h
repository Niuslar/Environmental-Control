/*
 * CCO2Controller.h
 *
 *  Created on: Mar 6, 2023
 *      Author: salavat.magazov
 */

#ifndef CCO2CONTROLLER_H_
#define CCO2CONTROLLER_H_

#include <CController.h>
#include <FreeRTOS_CLI.h>
#include <freertos_os2.h>

class CCO2Controller : public CController
{
public:
    CCO2Controller(uint32_t run_period,
                   const etl::string<configMAX_TASK_NAME_LEN> name,
                   uint32_t stack_depth,
                   osPriority_t priority);
    virtual ~CCO2Controller();

    virtual void run();

    static BaseType_t requestCO2(char *pcWriteBuffer,
                                 size_t xWriteBufferLen,
                                 const char *pcCommandString);
};

#endif /* CCO2CONTROLLER_H_ */
