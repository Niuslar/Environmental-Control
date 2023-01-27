/*
 * CMessage.h
 *
 *  Created on: Jan 27, 2023
 *      Author: salavat.magazov
 */

#ifndef INC_CMESSAGE_H_
#define INC_CMESSAGE_H_

#include "IComChannel.h"
#include "ICommand.h"

class CMessage : public ICommand
{
public:
    CMessage();
    virtual ~CMessage();

    virtual const etl::string<MAX_COMMAND_SIZE> *getName() const;

    virtual unsigned int getArgumentCount() const;

    virtual const etl::string<MAX_COMMAND_SIZE> *getStringArgument() const;

    virtual float &operator[](unsigned int index);

private:
    etl::string<MAX_COMMAND_SIZE> m_command_name;
    uint32_t m_argument_count;
    float m_arguments[MAX_ARGUMENT_COUNT];
    etl::string<MAX_COMMAND_SIZE> m_string_argument;
    IComChannel *mp_return_address;
};

#endif /* INC_CMESSAGE_H_ */
