/* GStreamer
 * Copyright (C) 2017 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_NUMBERSINK_H_
#define _GST_NUMBERSINK_H_

#include <gst/base/gstbasesink.h>

G_BEGIN_DECLS

#define GST_TYPE_NUMBERSINK   (gst_numbersink_get_type())
#define GST_NUMBERSINK(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_NUMBERSINK,GstNumbersink))
#define GST_NUMBERSINK_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_NUMBERSINK,GstNumbersinkClass))
#define GST_IS_NUMBERSINK(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_NUMBERSINK))
#define GST_IS_NUMBERSINK_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_NUMBERSINK))

typedef struct _GstNumbersink GstNumbersink;
typedef struct _GstNumbersinkClass GstNumbersinkClass;

struct _GstNumbersink
{
  GstBaseSink base_numbersink;

};

struct _GstNumbersinkClass
{
  GstBaseSinkClass base_numbersink_class;
};

GType gst_numbersink_get_type (void);

G_END_DECLS

#endif
