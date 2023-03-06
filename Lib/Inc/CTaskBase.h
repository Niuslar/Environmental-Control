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

    /**
     * @fn void run()=0
     * @brief Method prototype for what task is supposed to do.
     *
     * @note This method cannot return. If this method returns, the FreeRTOS
     * kernel will crash. If task no longer needed, it must be deleted using
     * proper FreeRTOS API.
     */
    __attribute((noreturn)) virtual void run() = 0;

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

#if (configUSE_OS2_THREAD_SUSPEND_RESUME == 1)
    /**
     * @fn bool suspend()
     * @brief Suspend active task. Task will be frozen until resumed.
     */
    void suspend();

    /**
     * @fn void resume()
     * @brief Resume suspended task. Task will start executing from same state
     * it was suspended.
     */
    void resume();
#endif

    // TODO: Need to add service functionality such as stack high water mark,
    // task stats, etc.

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
    const uint32_t m_stack_depth;
    osPriority_t m_priority;
    osThreadId_t m_id;
};

#endif /* CTASKBASE_H_ */
