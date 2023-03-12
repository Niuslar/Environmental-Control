/*
 * CRealHardwareMap.h
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#ifndef CREALHARDWAREMAP_H_
#define CREALHARDWAREMAP_H_

#include <CController.h>
#include <FreeRTOS_CLI.h>
#include <freertos_os2.h>

class CRealHardwareMap : public CController
{
public:
    CRealHardwareMap(uint32_t run_period,
                     const etl::string<configMAX_TASK_NAME_LEN> name,
                     uint32_t stack_depth,
                     osPriority_t priority);
    virtual ~CRealHardwareMap();
    /*
     * CController methods
     */
    virtual void run();

    static BaseType_t requestHw(char *pcWriteBuffer,
                                size_t xWriteBufferLen,
                                const char *pcCommandString);
};

#endif /* CREALHARDWAREMAP_H_ */
