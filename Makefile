
CFLAGS=-c -Wall $(IFLAGS) -g
OUTDIR=out
IFLAGS=-I$(OUTDIR)/include -Ideps/box2d/Box2D -Ideps/v8/include -Isrc/common -Isrc/common/binding -Isrc/common/components -Isrc/common/renderer -Isrc/common/resource
OBJ_DIR=$(OUTDIR)/objs
SOURCES:=$(shell find src -name \*.cpp)
OBJECTS:=$(patsubst src/%.cpp,out/%.o,$(SOURCES))
BASE_DIR=${PWD}
LIBPNG_CPPFLAGS=-I$(BASE_DIR)/$(OUTDIR)/include
LIBPNG_LDFLAGS=-L$(BASE_DIR)/$(OUTDIR)/lib
TARGET=flatland
UNAME = $(shell uname -s)
LDFLAGS=-L$(OUTDIR)/lib -lpng -lz -lv8_base -lv8_snapshot -lBox2D

ifeq ($(UNAME),Darwin)
CC=clang++
V8BUILDDIR=deps/v8/out/native
else
CC=g++
V8BUILDDIR=deps/v8/out/native/obj.target/tools/gyp
LDFLAGS+=-lGL
endif


all: create-out $(TARGET)

clean: zlib-clean libpng-clean sdl-clean v8-clean box2d-clean $(TARGET)-clean

create-out:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUTDIR)/lib

dependencies: zlib libpng-configure
	$(MAKE) -C deps/v8 dependencies
	mkdir -p out/deps/SDL && cd out/deps/SDL && ../../../deps/SDL/configure --prefix=${BASE_DIR}/out

box2d: box2d-build
	test -f out/lib/libBox2D.a || $(MAKE) -C deps/box2d/Box2D -f Makefile.flatland install

box2d-build:
	$(MAKE) -C deps/box2d/Box2D -f Makefile.flatland

box2d-clean:
	$(MAKE) -C deps/box2d/Box2D -f Makefile.flatland clean

v8:
	$(MAKE) -C deps/v8 native -j8
	cp $(V8BUILDDIR)/*.a $(OUTDIR)/lib

v8-clean:
	$(MAKE) -C deps/v8 clean

libpng-configure:
	mkdir -p out/deps/libpng
	cd out/deps/libpng && LDFLAGS=$(LIBPNG_LDFLAGS) CPPFLAGS=$(LIBPNG_CPPFLAGS) ../../../deps/libpng/configure --enable-static --disable-shared --with-zlib-prefix=${BASE_DIR}/out --prefix=${BASE_DIR}/out

libpng: libpng-build
	test -f out/lib/libpng.a || $(MAKE) -C out/deps/libpng install

libpng-build:
	$(MAKE) -C out/deps/libpng

libpng-clean:
	$(MAKE) -C out/deps/libpng clean

zlib: zlib-build
	test -f out/lib/libz.a || $(MAKE) -C deps/zlib install

zlib-build: zlib-prepare
	$(MAKE) -C deps/zlib

zlib-prepare: create-out
	-$(shell cd deps/zlib &&./configure --static --prefix=${BASE_DIR}/out)

zlib-clean:
	$(MAKE) -C deps/zlib distclean

sdl: sdl-build
	test -f out/lib/libSDL2.a || $(MAKE) -C out/deps/SDL install

sdl-build:
	$(MAKE) -C out/deps/SDL

sdl-clean:
	$(MAKE) -C out/deps/SDL clean

$(TARGET)-clean:
	rm -rf $(OUTDIR)/obj
	rm -rf $(OUTDIR)/$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(shell out/bin/sdl2-config --static-libs) -o $(OUTDIR)/$@
	rm -rf $(OUTDIR)/builtins
	cp -R src/lib $(OUTDIR)/builtins

$(OBJECTS): out/%.o : src/%.cpp libpng v8 sdl box2d
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(shell out/bin/sdl2-config --cflags) -c $< -o $@
