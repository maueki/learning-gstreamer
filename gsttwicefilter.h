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

#ifndef _GST_TWICEFILTER_H_
#define _GST_TWICEFILTER_H_

#include <gst/base/gstbasetransform.h>

G_BEGIN_DECLS

#define GST_TYPE_TWICEFILTER   (gst_twicefilter_get_type())
#define GST_TWICEFILTER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_TWICEFILTER,GstTwicefilter))
#define GST_TWICEFILTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_TWICEFILTER,GstTwicefilterClass))
#define GST_IS_TWICEFILTER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_TWICEFILTER))
#define GST_IS_TWICEFILTER_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_TWICEFILTER))

typedef struct _GstTwicefilter GstTwicefilter;
typedef struct _GstTwicefilterClass GstTwicefilterClass;

struct _GstTwicefilter
{
  GstBaseTransform base_twicefilter;

};

struct _GstTwicefilterClass
{
  GstBaseTransformClass base_twicefilter_class;
};

GType gst_twicefilter_get_type (void);

G_END_DECLS

#endif
