/*
 * CCommandController.h
 *
 *  Created on: Mar 7, 2023
 *      Author: salavat.magazov
 */

#ifndef CCOMMANDCONTROLLER_H_
#define CCOMMANDCONTROLLER_H_

#include <CTaskBase.h>
#include "IComChannel.h"

// Note that this number cannot exceed 31.
static constexpr uint32_t MAX_COM_CHANNELS = 10;

class CCommandController : public CTaskBase
{
public:
    CCommandController(const etl::string<configMAX_TASK_NAME_LEN> name,
                       uint32_t stack_depth,
                       osPriority_t priority);
    virtual ~CCommandController();

    __attribute((noreturn)) virtual void run();

    /**
     * @fn uint32_t registerComChannel(IComChannel*)
     * @brief Register com channel with the command controller to let it know to
     * expect command traffic from that channel
     *
     * @note Channels should be registered in order of priority since first
     * registered will be served first.
     *
     * @param p_com_channel Pointer to the IComChannel instance.
     * @return Bit map of the IComChannel instance that it needs to trigger when
     * notifying of available data.
     */
    uint32_t registerComChannel(IComChannel *p_com_channel);

private:
    uint8_t getIndexFromFlag(uint32_t flag);
    void processChannel(IComChannel *p_channel);

    uint8_t m_com_channel_counter;
    uint32_t m_com_channel_flags;
    IComChannel *mp_registered_channels[MAX_COM_CHANNELS];

    uint32_t m_active_flags;
    uint8_t m_active_index;
    etl::string<MAX_STRING_SIZE> m_active_command;
    char m_response[MAX_STRING_SIZE];
};

#endif /* CCOMMANDCONTROLLER_H_ */
