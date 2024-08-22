/* GLIB - Library of useful routines for C programming
 * Copyright (c) 2024  Florian "sp1rit" <sp1rit@disroot.org>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "glib-androidprivate.h"

static jobject g_android_context;

struct _GAndroidCache
{
  struct
  {
    jclass klass;
  } a_context;
} g_android_cache;

/**
 * g_android_get_context:
 *
 * Get the reference to to the android.content.Context object set in
 * [func@GLib.android_set_context].
 *
 *
 * The
 * [Context](https://developer.android.com/reference/android/content/Context)
 * object is the central interface to interact with the Android
 * operating system.
 *
 * Do not call this function after [func@GLib.java_finalize] has been
 * called.
 *
 * Returns: the context object
 * Since: 2.86
 */
jobject
g_android_get_context (void)
{
  return g_android_context;
}

/**
 * g_android_set_context:
 * @context: the android.content.Context object
 *
 * Set the context object that glib shoud use when interacting with the
 * Android operating system.
 *
 *
 * GLib will only use the @context object of the initial call to this
 * function. All further calls are ignored.
 *
 * Returns: %TRUE if sucessful, %FALSE if this function has already been
 *   called
 * Since: 2.86
 */
gboolean
g_android_set_context (jobject context)
{
  g_return_val_if_fail (context != NULL, FALSE);
  if (g_android_context)
    return FALSE;

  GJavaScope env = g_java_enter_scope(1);
  g_android_context = (*env)->NewGlobalRef(env, context);

  jclass context_class = (*env)->FindClass(env, "android/content/Context");
  g_android_cache.a_context.klass = (*env)->NewGlobalRef(env, context_class);

  g_java_leave_scope(&env);
  return TRUE;
}

void
g_android_finalize (void)
{
  JNIEnv *env = g_java_get_env();
  (*env)->DeleteGlobalRef(env, g_android_cache.a_context.klass);
  (*env)->DeleteGlobalRef(env, g_android_context);
  g_android_context = NULL;
}
