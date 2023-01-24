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
#include "etl/string.h"
#include "task.h"

class CTaskBase
{
public:
    CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
              uint16_t stack_depth,
              UBaseType_t priority);
    virtual ~CTaskBase();

    virtual void run() = 0;

    virtual bool start();

    static void taskRunner(void *p_param);

protected:
    void delay(const TickType_t delay);
    void delayUntil(TickType_t *const p_previous_wake_time,
                    const TickType_t delay);

private:
    TaskHandle_t m_handle;
    etl::string<configMAX_TASK_NAME_LEN> m_name;
    const UBaseType_t m_stack_depth;
    UBaseType_t m_priority;
};

#endif /* CTASKBASE_H_ */
