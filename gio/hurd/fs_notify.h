/* GIO - GLib Input, Output and Streaming Library
 *
 * Copyright (C) 2022-2025 Sergey Bugaev
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "ghurdfilemonitor.h"

/* This declaration exists solely to appease MIG;
   regular C code should not use it.  */
typedef GHurdFileMonitor *ghurdfilemonitor_t;

GHurdFileMonitor *g_hurd_file_monitor_lookup_by_port (mach_port_t);
GHurdFileMonitor *g_hurd_file_monitor_lookup_by_payload (uintptr_t);
void g_hurd_file_monitor_unref0 (GHurdFileMonitor *monitor);

boolean_t fs_notify_server (mach_msg_header_t *, mach_msg_header_t *);
