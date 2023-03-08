/**
 * @file IComChannel.h
 *
 */

/*
 * IComChannel.h
 *
 *  Created on: 16 Feb 2022
 *      Author: salavat.magazov
 */

#ifndef ICOMCHANNEL_H_
#define ICOMCHANNEL_H_

#include "etl/string.h"

class CTaskBase;

class IComChannel
{
public:
    IComChannel(etl::string<MAX_STRING_SIZE> name)
        : mp_notify_task(nullptr),
          m_notify_flag(0),
          m_name(name){};

    etl::string<MAX_STRING_SIZE> getName() const
    {
        return m_name;
    };

    virtual bool isDataAvailable() = 0;
    virtual etl::string<MAX_STRING_SIZE> getData() = 0;
    virtual bool send(etl::string<MAX_STRING_SIZE> message) = 0;
    virtual bool send(char const *p_data_buf, uint32_t len) = 0;
    virtual void registerTask(CTaskBase *p_task, uint32_t flag)
    {
        mp_notify_task = p_task;
        m_notify_flag = flag;
    }

protected:
    CTaskBase *mp_notify_task;
    uint32_t m_notify_flag;

private:
    etl::string<MAX_STRING_SIZE> const m_name;
};

#endif /* ICOMCHANNEL_H_ */
