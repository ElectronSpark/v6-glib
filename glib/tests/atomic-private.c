/*
 * Copyright © 2026 Luca Bacci
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://gnu.org/licenses/>.
 */

#include <glib.h>
#include "gatomicprivate.h"

static void
test_types (void)
{
  const gint *csp;
  const gint * const *cspp;
  guint u, u2;
  gint s, s2;
  gpointer vp, vp2;
  const char *vp_str;
  const char *volatile vp_str_vol;
  const char *str = "Hello";
  const char *old_str;
  int *ip, *ip2;
  guintptr gu, gu2;
  gboolean res;

  csp = &s;
  cspp = &csp;

  /* relaxed */

  g_atomic_int_set_relaxed (&u, 5);
  u2 = (guint) g_atomic_int_get_relaxed (&u);
  g_assert_cmpuint (u2, ==, 5);

  g_atomic_int_set_relaxed (&s, 5);
  s2 = g_atomic_int_get_relaxed (&s);
  g_assert_cmpint (s2, ==, 5);

  g_atomic_pointer_set_relaxed (&vp, 0);
  vp2 = g_atomic_pointer_get_relaxed (&vp);
  g_assert_true (vp2 == 0);

  /* Note that atomic variables should almost certainly not be marked as
   * `volatile` — see http://isvolatileusefulwiththreads.in/c/. This test exists
   * to make sure that we don’t warn when built against older third party code. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunknown-warning-option"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
  g_atomic_pointer_set_relaxed (&vp_str_vol, NULL);
  g_atomic_pointer_set_relaxed (&vp_str, str);
  res = g_atomic_pointer_compare_and_exchange (&vp_str_vol, NULL, str);
  g_assert_true (res);
  g_assert_cmpstr (g_atomic_pointer_exchange (&vp_str, NULL), ==, str);
  g_assert_null (vp_str);

  res = g_atomic_pointer_compare_and_exchange_full (&vp_str_vol, str, NULL, &old_str);
  g_assert_true (res);
  g_assert_true (old_str == str);
#pragma GCC diagnostic pop

  g_atomic_pointer_set_relaxed (&ip, 0);
  ip2 = g_atomic_pointer_get_relaxed (&ip);
  g_assert_true (ip2 == 0);

  g_atomic_pointer_set_relaxed (&gu, 0);
  vp2 = (gpointer) g_atomic_pointer_get_relaxed (&gu);
  gu2 = (guintptr) vp2;
  g_assert_cmpuint (gu2, ==, 0);

  g_assert_cmpint (g_atomic_int_get_relaxed (csp), ==, s);
  g_assert_true (g_atomic_pointer_get_relaxed ((const gint **) cspp) == csp);

  /* acquire / release */

  g_atomic_int_set_release (&u, 5);
  u2 = (guint) g_atomic_int_get_acquire (&u);
  g_assert_cmpuint (u2, ==, 5);

  g_atomic_int_set_release (&s, 5);
  s2 = g_atomic_int_get_acquire (&s);
  g_assert_cmpint (s2, ==, 5);

  g_atomic_pointer_set_release (&vp, 0);
  vp2 = g_atomic_pointer_get_acquire (&vp);
  g_assert_true (vp2 == 0);

  /* Note that atomic variables should almost certainly not be marked as
   * `volatile` — see http://isvolatileusefulwiththreads.in/c/. This test exists
   * to make sure that we don’t warn when built against older third party code. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunknown-warning-option"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
  g_atomic_pointer_set_release (&vp_str_vol, NULL);
  g_atomic_pointer_set_release (&vp_str, str);
  res = g_atomic_pointer_compare_and_exchange (&vp_str_vol, NULL, str);
  g_assert_true (res);
  g_assert_cmpstr (g_atomic_pointer_exchange (&vp_str, NULL), ==, str);
  g_assert_null (vp_str);

  res = g_atomic_pointer_compare_and_exchange_full (&vp_str_vol, str, NULL, &old_str);
  g_assert_true (res);
  g_assert_true (old_str == str);
#pragma GCC diagnostic pop

  g_atomic_pointer_set_release (&ip, 0);
  ip2 = g_atomic_pointer_get_acquire (&ip);
  g_assert_true (ip2 == 0);

  g_atomic_pointer_set_release (&gu, 0);
  vp2 = (gpointer) g_atomic_pointer_get_acquire (&gu);
  gu2 = (guintptr) vp2;
  g_assert_cmpuint (gu2, ==, 0);

  g_assert_cmpint (g_atomic_int_get_acquire (csp), ==, s);
  g_assert_true (g_atomic_pointer_get_acquire ((const gint **) cspp) == csp);
}

int
main (int argc, char **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/atomic-private/types", test_types);

  return g_test_run ();
}
