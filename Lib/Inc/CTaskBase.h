/*
 * CTaskBase.h
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#ifndef CTASKBASE_H_
#define CTASKBASE_H_

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "cmsis_os2.h"
#include "etl/string.h"

class CTaskBase
{
public:
    CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
              uint32_t stack_depth,
			  osPriority_t priority);
    virtual ~CTaskBase();

    virtual void run() = 0;

    virtual bool start();

    static void taskRunner(void *p_param);

private:
    etl::string<configMAX_TASK_NAME_LEN> m_name;
    const uint32_t m_stack_depth;
    osPriority_t m_priority;
    osThreadId_t m_id;
};

#endif /* CTASKBASE_H_ */
