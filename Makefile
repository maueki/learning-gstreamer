
CFLAGS:=-Wno-unused-function

.SUFFIXES: .c .o .so
.PHONY: all clean inspect

all: gstnumbersink.so gstnumbersrc.so

.c.o:
	gcc -Wall -Werror -fPIC ${CFLAGS} $(shell pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0) -c $<

.o.so:
	gcc -shared $(shell pkg-config --libs gstreamer-1.0 gstreamer-base-1.0) -o $@ $<
	gst-inspect-1.0 $@

clean:
	rm -f *.o *.so
