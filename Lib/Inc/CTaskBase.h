/*
 * CTaskBase.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Niuslar
 */

#ifndef INC_CTASKBASE_H_
#define INC_CTASKBASE_H_

#include "FreeRTOS.h"
#include "task.h"
#include <etl/string.h>
#include "main.h"

class CTaskBase
{
public:
	CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
			configSTACK_DEPTH_TYPE stack_depth,
			UBaseType_t priority);
	~CTaskBase();

	__attribute((noreturn))virtual void run() = 0;

    /**
     * @fn bool start()
     * @brief Call this method to start executing the task.
     *
     * @note This function does not "start" the thread execution. It registers
     * the thread function pointer with FreeRTOS kernel. The actual execution
     * starts when kernel decides that it's time for thread to start based on
     * kernel settings and task priority.
     *
     * @return True if task started successfully. false otherwise.
     */
    bool start();

protected:

    /**
     * @fn void taskRunner(void*)
     * @brief Mechanism to satisfy FreeRTOS API need to call specific function
     * prototype.
     *
     * @note This method is registered with FreeRTOS kernel as a function to
     * call when task is executed. The method has to be static to have correct
     * prototype. The actual code to be ran when task is active is in ::run()
     * method, which gets called inside this static method. Specific instance of
     * TaskBase class is identified during call to ::start() method where
     * pointer to class instance is passed on as a parameter.
     *
     * @param p_param
     */
    static void taskRunner(void *p_param);

private:
    etl::string<configMAX_TASK_NAME_LEN> m_name;
	configSTACK_DEPTH_TYPE m_stack_depth;
	UBaseType_t m_priority;

	TaskHandle_t m_task_handle;
};




#endif /* INC_CTASKBASE_H_ */
