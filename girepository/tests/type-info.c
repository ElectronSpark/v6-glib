/*
 * Copyright 2025 Philip Chimento <philip.chimento@gmail.com>
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

#include "girepository.h"
#include "test-common.h"

static void
test_type_info_name (RepositoryFixture *fx,
                     const void *unused)
{
  GIInterfaceInfo *interface_info = NULL;
  GIVFuncInfo *vfunc;
  GITypeInfo *typeinfo;

  g_test_summary ("Test that gi_base_info_get_name() returns null for GITypeInfo");
  g_test_bug ("https://gitlab.gnome.org/GNOME/gobject-introspection/issues/96");

  interface_info = GI_INTERFACE_INFO (gi_repository_find_by_name (fx->repository, "Gio", "File"));
  g_assert_nonnull (interface_info);
  vfunc = gi_interface_info_find_vfunc (interface_info, "read_async");
  g_assert_nonnull (vfunc);

  typeinfo = gi_callable_info_get_return_type (GI_CALLABLE_INFO (vfunc));
  g_assert_nonnull (typeinfo);

  g_assert_null (gi_base_info_get_name (GI_BASE_INFO (typeinfo)));

  g_clear_pointer (&interface_info, gi_base_info_unref);
  g_clear_pointer (&vfunc, gi_base_info_unref);
  g_clear_pointer (&typeinfo, gi_base_info_unref);
}

int
main (int argc, char **argv)
{
  repository_init (&argc, &argv);

  ADD_REPOSITORY_TEST ("/type-info/name", test_type_info_name, &typelib_load_spec_gio);

  return g_test_run ();
}
