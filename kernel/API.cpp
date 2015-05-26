/*
 * Copyright (C) 2015 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "API.h"

API::API()
{
    // Register generic API handlers
    m_apis.fill(ZERO);
    m_apis.insert(IPCMessageNumber, (Handler *) IPCMessageHandler);
    m_apis.insert(PrivExecNumber,   (Handler *) PrivExecHandler);
    m_apis.insert(ProcessCtlNumber, (Handler *) ProcessCtlHandler);
    m_apis.insert(SystemInfoNumber, (Handler *) SystemInfoHandler);
    m_apis.insert(VMCopyNumber,     (Handler *) VMCopyHandler);
    m_apis.insert(VMCtlNumber,      (Handler *) VMCtlHandler);
    m_apis.insert(IOCtlNumber,      (Handler *) IOCtlHandler);
}

Error API::invoke(Number number,
                  ulong arg1,
                  ulong arg2,
                  ulong arg3,
                  ulong arg4,
                  ulong arg5)
{
    Handler **handler = (Handler **) m_apis.get(number);

    if (handler)
        return (*handler)(arg1, arg2, arg3, arg4, arg5);
    else
        return InvalidArgument;
}

Log & operator << (Log &log, API::Operation op)
{
    switch (op)
    {
        case API::Create:      log.write("Create");      break;
        case API::Delete:      log.write("Delete");      break;
        case API::Send:        log.write("Send");        break;
        case API::Receive:     log.write("Receive");     break;
        case API::SendReceive: log.write("SendReceive"); break;
        case API::Read:        log.write("Read");        break;
        case API::Write:       log.write("Write");       break;
    }    
    return log;
}
