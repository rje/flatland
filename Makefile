
CC=clang++
IFLAGS=-Ideps/v8/include -Isrc/common -Isrc/common/binding -Isrc/common/components -Isrc/common/renderer -Isrc/osx -Iout/include
CFLAGS=-c -Wall $(IFLAGS)
OUTDIR=out
OBJ_DIR=$(OUTDIR)/objs
LDFLAGS=-L$(OUTDIR)/lib -lv8_base -lv8_snapshot
SOURCES:=$(shell find src -name \*.cpp)
OBJECTS:=$(patsubst src/%.cpp,out/%.o,$(SOURCES))
BASE_DIR=${PWD}
TARGET=flatland

all: create-out $(TARGET)

clean: sdl-clean v8-clean $(TARGET)-clean

create-out:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OUTDIR)/lib

dependencies:
	$(MAKE) -C deps/v8 dependencies
	$(shell cd deps/SDL && ./configure --prefix=${BASE_DIR}/out)

v8:
	make -C deps/v8 native
	cp deps/v8/out/native/*.a $(OUTDIR)/lib

v8-clean:
	make -C deps/v8 clean

sdl: sdl-build
	test -f out/lib/libSDL2.a || make -C deps/SDL install

sdl-build:
	make -C deps/SDL

sdl-clean:
	make -C deps/SDL clean

$(TARGET)-clean:
	rm -rf $(OUTDIR)/obj
	rm -rf $(OUTDIR)/$(TARGET)

$(TARGET): | v8 sdl $(OBJECTS)
	$(CC) $(LDFLAGS) $(shell out/bin/sdl2-config --static-libs) $(OBJ_DIR)/* -o $(OUTDIR)/$@

$(OBJECTS): out/%.o : src/%.cpp 
	$(CC) $(CFLAGS) $(shell out/bin/sdl2-config --cflags) $< -o $(OBJ_DIR)/$(notdir $@)
