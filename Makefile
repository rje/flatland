
IFLAGS=-Ideps/box2d/Box2D -Ideps/v8/include -Isrc/common -Isrc/common/binding -Isrc/common/components -Isrc/common/renderer
CFLAGS=-c -Wall $(IFLAGS)
OUTDIR=out
OBJ_DIR=$(OUTDIR)/objs
SOURCES:=$(shell find src -name \*.cpp)
OBJECTS:=$(patsubst src/%.cpp,out/%.o,$(SOURCES))
BASE_DIR=${PWD}
TARGET=flatland
UNAME = $(shell uname -s)
LDFLAGS=-L$(OUTDIR)/lib -lv8_base -lv8_snapshot -lBox2D

ifeq ($(UNAME),Darwin)
CC=clang++
V8BUILDDIR=deps/v8/out/native
else
CC=g++
V8BUILDDIR=deps/v8/out/native/obj.target/tools/gyp
LDFLAGS+=-lGL
endif


all: create-out $(TARGET)

clean: sdl-clean v8-clean box2d-clean $(TARGET)-clean

create-out:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUTDIR)/lib

dependencies:
	$(MAKE) -C deps/v8 dependencies
	$(shell mkdir -p out/deps/SDL && cd out/deps/SDL && ../../../deps/SDL/configure --prefix=${BASE_DIR}/out)

box2d: box2d-build
	test -f out/lib/libBox2D.a || make -C deps/box2d/Box2D -f Makefile.flatland install

box2d-build:
	make -C deps/box2d/Box2D -f Makefile.flatland

box2d-clean:
	make -C deps/box2d/Box2D -f Makefile.flatland clean

v8:
	make -C deps/v8 native -j8
	cp $(V8BUILDDIR)/*.a $(OUTDIR)/lib

v8-clean:
	make -C deps/v8 clean

sdl: sdl-build
	test -f out/lib/libSDL2.a || make -C out/deps/SDL install

sdl-build:
	make -C out/deps/SDL

sdl-clean:
	make -C out/deps/SDL clean

$(TARGET)-clean:
	rm -rf $(OUTDIR)/obj
	rm -rf $(OUTDIR)/$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(shell out/bin/sdl2-config --static-libs) -o $(OUTDIR)/$@

$(OBJECTS): out/%.o : src/%.cpp v8 sdl box2d
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(shell out/bin/sdl2-config --cflags) -c $< -o $@
