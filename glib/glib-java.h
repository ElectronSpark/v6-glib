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

#ifndef __GLIB_JAVA_H__
#define __GLIB_JAVA_H__

#include <glib.h>
#ifndef G_HAVE_JAVA_SUPPORT
#error "This header may only be used if GLib was compiled with Java support"
#endif

#include <jni.h>

G_BEGIN_DECLS

GLIB_AVAILABLE_IN_2_86
gboolean glib_java_initialize     (JavaVM *vm, jobject class_loader);

GLIB_AVAILABLE_IN_2_86
gboolean glib_java_is_initialized (void);

GLIB_AVAILABLE_IN_2_86
void glib_java_finalize           (void);


GLIB_AVAILABLE_IN_2_86
JNIEnv *g_java_get_env (void);


typedef struct _GJavaThreadSentinel GJavaThreadSentinel;

GLIB_AVAILABLE_IN_2_86
GJavaThreadSentinel *g_java_enter_thread (void);

GLIB_AVAILABLE_IN_2_86
void g_java_leave_thread                 (GJavaThreadSentinel *self);


GLIB_AVAILABLE_IN_2_86
jobject g_java_get_class_loader (void);


typedef JNIEnv *GJavaScope;

GLIB_AVAILABLE_IN_2_86
GJavaScope g_java_enter_scope       (gint capacity);

GLIB_AVAILABLE_IN_2_86
void g_java_leave_scope             (GJavaScope* self);

GLIB_AVAILABLE_IN_2_86
jobject g_java_leave_scope_with_ref (GJavaScope* self,
                                     jobject ref);

G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC    (GJavaScope, g_java_leave_scope)


GLIB_AVAILABLE_IN_2_86
jclass g_java_find_class (const gchar* klass);

G_END_DECLS

#endif /* __GLIB_JAVA_H__ */
