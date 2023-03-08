/*
 * CCommandController.cpp
 *
 *  Created on: Mar 7, 2023
 *      Author: salavat.magazov
 */

#include <CCommandController.h>
#include "FreeRTOS_CLI.h"

CCommandController::CCommandController(
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CTaskBase(name, stack_depth, priority),
      m_com_channel_counter(0),
      m_com_channel_flags(0x00),
      mp_registered_channels{nullptr},
      m_active_flags(0x00),
      m_active_index(0)
{
}

CCommandController::~CCommandController()
{
    // TODO Auto-generated destructor stub
}

__attribute((noreturn)) void CCommandController::run()
{
    osThreadFlagsClear(m_com_channel_flags);
    while (true)
    {
        m_active_flags = osThreadFlagsWait(m_com_channel_flags,
                                           osFlagsWaitAny | osFlagsNoClear,
                                           osWaitForever);
        /* Once execution gets to this point there is one or more com channels
         * that have traffic arriving and that traffic requires processing.
         */
        while (m_active_flags > 0)
        {
            m_active_index = getIndexFromFlag(m_active_flags);
            processChannel(mp_registered_channels[m_active_index]);
        }
    }
}

uint32_t CCommandController::registerComChannel(IComChannel *p_com_channel)
{
    uint8_t channel_flag = 0;
    if (m_com_channel_counter < MAX_COM_CHANNELS)
    {
        mp_registered_channels[m_com_channel_counter] = p_com_channel;
        m_com_channel_counter++;
        channel_flag = 1 << m_com_channel_counter;
        m_com_channel_flags |= channel_flag;
    }
    return channel_flag;
}

uint8_t CCommandController::getIndexFromFlag(uint32_t flag)
{
    uint8_t index = 0;
    if (flag != 0)
    {
        flag >>= 1;
        while ((flag & 0x01) != 0x01)
        {
            flag >>= 1;
            index++;
        }
    }
    return index;
}

void CCommandController::processChannel(IComChannel *p_channel)
{
    uint32_t more_data;
    do
    {
        m_active_command = p_channel->getData();
        more_data = FreeRTOS_CLIProcessCommand(m_active_command.c_str(),
                                               m_response,
                                               MAX_STRING_SIZE);
        p_channel->send(m_response, strlen(m_response));
    } while (more_data != pdFALSE);
    /*
     * Clear the channel notification once all traffic has been dealt with.
     */
    uint32_t map = 2 << m_active_index;
    osThreadFlagsClear(map);
    m_active_flags &= ~map;
}
