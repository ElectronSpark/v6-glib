# GIO - GLib Input, Output and Streaming Library
#
# Copyright (C) 2022-2025 Sergey Bugaev
#
# SPDX-License-Identifier: LGPL-2.1-or-later
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General
# Public License along with this library; if not, see <http://www.gnu.org/licenses/>.

mig = find_program('mig')

fs_notify = custom_target('fs_notify',
  input : 'fs_notify.defs',
  output : ['fs_notifyServer.c', 'fs_notify_S.h'],
  command : [mig, '-n',
            '-server', '@OUTPUT0@',
            '-sheader', '@OUTPUT1@',
            '@INPUT@'])

hurd_sources = [
  'ghurdfilemonitor.c',
  fs_notify,
]

hurd_lib = static_library('hurd',
  sources : hurd_sources,
  include_directories : [configinc, glibinc, gmoduleinc],
  dependencies : [gioenumtypes_dep, libglib_dep, libgobject_dep],
  gnu_symbol_visibility : 'hidden',
  pic : true,
  c_args : [gio_c_args, gio_c_args_internal])
