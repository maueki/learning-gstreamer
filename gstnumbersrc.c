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
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-gstnumbersrc
 *
 * The numbersrc element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! numbersrc ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasesrc.h>
#include "gstnumbersrc.h"

#include <string.h>

GST_DEBUG_CATEGORY_STATIC (gst_numbersrc_debug_category);
#define GST_CAT_DEFAULT gst_numbersrc_debug_category

/* prototypes */


static void gst_numbersrc_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_numbersrc_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_numbersrc_dispose (GObject * object);
static void gst_numbersrc_finalize (GObject * object);

static GstCaps *gst_numbersrc_get_caps (GstBaseSrc * src, GstCaps * filter);
static gboolean gst_numbersrc_negotiate (GstBaseSrc * src);
static GstCaps *gst_numbersrc_fixate (GstBaseSrc * src, GstCaps * caps);
static gboolean gst_numbersrc_set_caps (GstBaseSrc * src, GstCaps * caps);
static gboolean gst_numbersrc_decide_allocation (GstBaseSrc * src,
    GstQuery * query);
static gboolean gst_numbersrc_start (GstBaseSrc * src);
static gboolean gst_numbersrc_stop (GstBaseSrc * src);
static void gst_numbersrc_get_times (GstBaseSrc * src, GstBuffer * buffer,
    GstClockTime * start, GstClockTime * end);
static gboolean gst_numbersrc_get_size (GstBaseSrc * src, guint64 * size);
static gboolean gst_numbersrc_is_seekable (GstBaseSrc * src);
static gboolean gst_numbersrc_prepare_seek_segment (GstBaseSrc * src,
    GstEvent * seek, GstSegment * segment);
static gboolean gst_numbersrc_do_seek (GstBaseSrc * src, GstSegment * segment);
static gboolean gst_numbersrc_unlock (GstBaseSrc * src);
static gboolean gst_numbersrc_unlock_stop (GstBaseSrc * src);
static gboolean gst_numbersrc_query (GstBaseSrc * src, GstQuery * query);
static gboolean gst_numbersrc_event (GstBaseSrc * src, GstEvent * event);
static GstFlowReturn gst_numbersrc_create (GstBaseSrc * src, guint64 offset,
    guint size, GstBuffer ** buf);
static GstFlowReturn gst_numbersrc_alloc (GstBaseSrc * src, guint64 offset,
    guint size, GstBuffer ** buf);
static GstFlowReturn gst_numbersrc_fill (GstBaseSrc * src, guint64 offset,
    guint size, GstBuffer * buf);

enum
{
  PROP_0
};

/* pad templates */

static GstStaticPadTemplate gst_numbersrc_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/unknown")
    );


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstNumbersrc, gst_numbersrc, GST_TYPE_BASE_SRC,
    GST_DEBUG_CATEGORY_INIT (gst_numbersrc_debug_category, "numbersrc", 0,
        "debug category for numbersrc element"));

static void
gst_numbersrc_class_init (GstNumbersrcClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseSrcClass *base_src_class = GST_BASE_SRC_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass),
      &gst_numbersrc_src_template);

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS (klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_numbersrc_set_property;
  gobject_class->get_property = gst_numbersrc_get_property;
  gobject_class->dispose = gst_numbersrc_dispose;
  gobject_class->finalize = gst_numbersrc_finalize;
/*
  base_src_class->get_caps = GST_DEBUG_FUNCPTR (gst_numbersrc_get_caps);
  base_src_class->negotiate = GST_DEBUG_FUNCPTR (gst_numbersrc_negotiate);
  base_src_class->fixate = GST_DEBUG_FUNCPTR (gst_numbersrc_fixate);
  base_src_class->set_caps = GST_DEBUG_FUNCPTR (gst_numbersrc_set_caps);
  base_src_class->decide_allocation =
      GST_DEBUG_FUNCPTR (gst_numbersrc_decide_allocation);
  base_src_class->start = GST_DEBUG_FUNCPTR (gst_numbersrc_start);
  base_src_class->stop = GST_DEBUG_FUNCPTR (gst_numbersrc_stop);
  base_src_class->get_times = GST_DEBUG_FUNCPTR (gst_numbersrc_get_times);
  base_src_class->get_size = GST_DEBUG_FUNCPTR (gst_numbersrc_get_size);
  base_src_class->is_seekable = GST_DEBUG_FUNCPTR (gst_numbersrc_is_seekable);
  base_src_class->prepare_seek_segment =
      GST_DEBUG_FUNCPTR (gst_numbersrc_prepare_seek_segment);
  base_src_class->do_seek = GST_DEBUG_FUNCPTR (gst_numbersrc_do_seek);
  base_src_class->unlock = GST_DEBUG_FUNCPTR (gst_numbersrc_unlock);
  base_src_class->unlock_stop = GST_DEBUG_FUNCPTR (gst_numbersrc_unlock_stop);
  base_src_class->query = GST_DEBUG_FUNCPTR (gst_numbersrc_query);
  base_src_class->event = GST_DEBUG_FUNCPTR (gst_numbersrc_event);
  base_src_class->create = GST_DEBUG_FUNCPTR (gst_numbersrc_create);
  base_src_class->alloc = GST_DEBUG_FUNCPTR (gst_numbersrc_alloc);
*/
  base_src_class->fill = GST_DEBUG_FUNCPTR (gst_numbersrc_fill);

}

static void
gst_numbersrc_init (GstNumbersrc * numbersrc)
{
}

void
gst_numbersrc_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (object);

  GST_DEBUG_OBJECT (numbersrc, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_numbersrc_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (object);

  GST_DEBUG_OBJECT (numbersrc, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_numbersrc_dispose (GObject * object)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (object);

  GST_DEBUG_OBJECT (numbersrc, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_numbersrc_parent_class)->dispose (object);
}

void
gst_numbersrc_finalize (GObject * object)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (object);

  GST_DEBUG_OBJECT (numbersrc, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS (gst_numbersrc_parent_class)->finalize (object);
}

/* get caps from subclass */
static GstCaps *
gst_numbersrc_get_caps (GstBaseSrc * src, GstCaps * filter)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "get_caps");

  return NULL;
}

/* decide on caps */
static gboolean
gst_numbersrc_negotiate (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "negotiate");

  return TRUE;
}

/* called if, in negotiation, caps need fixating */
static GstCaps *
gst_numbersrc_fixate (GstBaseSrc * src, GstCaps * caps)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "fixate");

  return NULL;
}

/* notify the subclass of new caps */
static gboolean
gst_numbersrc_set_caps (GstBaseSrc * src, GstCaps * caps)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "set_caps");

  return TRUE;
}

/* setup allocation query */
static gboolean
gst_numbersrc_decide_allocation (GstBaseSrc * src, GstQuery * query)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "decide_allocation");

  return TRUE;
}

/* start and stop processing, ideal for opening/closing the resource */
static gboolean
gst_numbersrc_start (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "start");

  return TRUE;
}

static gboolean
gst_numbersrc_stop (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "stop");

  return TRUE;
}

/* given a buffer, return start and stop time when it should be pushed
 * out. The base class will sync on the clock using these times. */
static void
gst_numbersrc_get_times (GstBaseSrc * src, GstBuffer * buffer,
    GstClockTime * start, GstClockTime * end)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "get_times");

}

/* get the total size of the resource in bytes */
static gboolean
gst_numbersrc_get_size (GstBaseSrc * src, guint64 * size)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "get_size");

  return TRUE;
}

/* check if the resource is seekable */
static gboolean
gst_numbersrc_is_seekable (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "is_seekable");

  return TRUE;
}

/* Prepare the segment on which to perform do_seek(), converting to the
 * current basesrc format. */
static gboolean
gst_numbersrc_prepare_seek_segment (GstBaseSrc * src, GstEvent * seek,
    GstSegment * segment)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "prepare_seek_segment");

  return TRUE;
}

/* notify subclasses of a seek */
static gboolean
gst_numbersrc_do_seek (GstBaseSrc * src, GstSegment * segment)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "do_seek");

  return TRUE;
}

/* unlock any pending access to the resource. subclasses should unlock
 * any function ASAP. */
static gboolean
gst_numbersrc_unlock (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "unlock");

  return TRUE;
}

/* Clear any pending unlock request, as we succeeded in unlocking */
static gboolean
gst_numbersrc_unlock_stop (GstBaseSrc * src)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "unlock_stop");

  return TRUE;
}

/* notify subclasses of a query */
static gboolean
gst_numbersrc_query (GstBaseSrc * src, GstQuery * query)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "query");

  return TRUE;
}

/* notify subclasses of an event */
static gboolean
gst_numbersrc_event (GstBaseSrc * src, GstEvent * event)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "event");

  return TRUE;
}

/* ask the subclass to create a buffer with offset and size, the default
 * implementation will call alloc and fill. */
static GstFlowReturn
gst_numbersrc_create (GstBaseSrc * src, guint64 offset, guint size,
    GstBuffer ** buf)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "create");

  return GST_FLOW_OK;
}

/* ask the subclass to allocate an output buffer. The default implementation
 * will use the negotiated allocator. */
static GstFlowReturn
gst_numbersrc_alloc (GstBaseSrc * src, guint64 offset, guint size,
    GstBuffer ** buf)
{
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);

  GST_DEBUG_OBJECT (numbersrc, "alloc");

  return GST_FLOW_OK;
}

/* ask the subclass to fill the buffer with data from offset and size */
static GstFlowReturn
gst_numbersrc_fill (GstBaseSrc * src, guint64 offset, guint size,
    GstBuffer * buf)
{
  static guint32 i = 0;
  GstNumbersrc *numbersrc = GST_NUMBERSRC (src);
  GstMapInfo info;

  GST_DEBUG_OBJECT (numbersrc, "fill");

  if (size < sizeof(i)) {
      GST_ERROR_OBJECT(numbersrc, "gst_numbersrc_fill: size too short");
      return GST_FLOW_ERROR;
  }

  if (!gst_buffer_map (buf, &info, GST_MAP_WRITE))
    return GST_FLOW_ERROR;

  guint8 *data = info.data;
  memcpy(data, &i, sizeof(i));
  i++;

  gst_buffer_unmap (buf, &info);
  gst_buffer_resize(buf, 0, sizeof(i));

  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "numbersrc", GST_RANK_NONE,
      GST_TYPE_NUMBERSRC);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.0.FIXME"
#endif
#ifndef PACKAGE
#define PACKAGE "FIXME_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "FIXME_package_name"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    numbersrc,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
