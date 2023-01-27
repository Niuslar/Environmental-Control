/*
 * CMessage.cpp
 *
 *  Created on: Jan 27, 2023
 *      Author: salavat.magazov
 */

#include <CMessage.h>

CMessage::CMessage()
    : m_command_name("\0"),
      m_argument_count(0),
      m_arguments{DEFAULT_ARGUMENT},
      m_string_argument("\0"),
      mp_return_address(NULL)
{
}

CMessage::~CMessage()
{
    // TODO Auto-generated destructor stub
}

const etl::string<MAX_COMMAND_SIZE> *CMessage::getName() const
{
    return &m_command_name;
}

unsigned int CMessage::getArgumentCount() const
{
    return m_argument_count;
}

const etl::string<MAX_COMMAND_SIZE> *CMessage::getStringArgument() const
{
    return &m_string_argument;
}

float &CMessage::operator[](unsigned int index)
{
    if (index < MAX_ARGUMENT_COUNT)
    {
        return m_arguments[index];
    }
}
