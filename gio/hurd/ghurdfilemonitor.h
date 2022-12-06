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

#ifndef __G_HURD_FILE_MONITOR_H__
#define __G_HURD_FILE_MONITOR_H__

#include <gio/glocalfilemonitor.h>

G_BEGIN_DECLS

#define G_TYPE_HURD_FILE_MONITOR		(g_hurd_file_monitor_get_type ())
#define G_HURD_FILE_MONITOR(o)			(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_HURD_FILE_MONITOR, GHurdFileMonitor))
#define G_HURD_FILE_MONITOR_CLASS(k)		(G_TYPE_CHECK_CLASS_CAST ((k), G_TYPE_HURD_FILE_MONITOR, GHurdFileMonitorClass))
#define G_IS_HURD_FILE_MONITOR(o)		(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_HURD_FILE_MONITOR))
#define G_IS_HURD_FILE_MONITOR_CLASS(k)		(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_HURD_FILE_MONITOR))
#define G_HURD_FILE_MONITOR_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_HURD_FILE_MONITOR, GHurdFileMonitorClass))

typedef struct _GHurdFileMonitor	GHurdFileMonitor;
typedef struct _GHurdFileMonitorClass	GHurdFileMonitorClass;

struct _GHurdFileMonitorClass
{
  GLocalFileMonitorClass parent_class;
};

GType g_hurd_file_monitor_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __G_HURD_FILE_MONITOR_H__ */
