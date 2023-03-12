/*
 * CRealHardwareMap.cpp
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#include <CRealHardwareMap.h>

static constexpr char command[] = "hw";
static constexpr char help[] =
    "hw [?] : \n "
    "? - return comprehensive low level report\n";

static constexpr CLI_Command_Definition_t get_hardware_map{
    command,
    help,
    &(CRealHardwareMap::requestHw)};

CRealHardwareMap::CRealHardwareMap(
    uint32_t run_period,
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CController(run_period, name, stack_depth, priority)
{
    FreeRTOS_CLIRegisterCommand(&get_hardware_map);
}

CRealHardwareMap::~CRealHardwareMap()
{
    // TODO Auto-generated destructor stub
}

/*
 * CController methods
 */

void CRealHardwareMap::run()
{
    while (true)
    {
        // TODO: this is where all data acquisition is happening. The other
        // methods are for accessing acquired data.
        osDelayUntil(m_run_period);
    }
}

// CLI command processors

BaseType_t CRealHardwareMap::requestHw(char *pcWriteBuffer,
                                       size_t xWriteBufferLen,
                                       const char *pcCommandString)
{
    // TODO: create a parser for commands.
    return 0;
}
