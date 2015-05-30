/*
 * Copyright (C) 2009 Niek Linnenbank
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

#include <KernelLog.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    const char *av[] = { "/bin/sh", "/etc/init.sh", ZERO };

    /* Open kernel logging facilities. */
    Log *log = new KernelLog();
    log->setMinimumLogLevel(Log::Notice);

    /*
     * TODO: give up all privileges.
     */
    NOTICE("Starting init script: " << av[1]);

    // Execute the run commands file
    forkexec("/bin/sh", av);

    // If we reach here the forkexec() failed.
    ERROR("forkexec() failed for /bin/sh: " <<
          strerror(errno));

    /* Exit immediately. */
    return EXIT_SUCCESS;
}
