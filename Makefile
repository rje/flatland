
CC=clang++
CFLAGS=-c -Wall
LDFLAGS=
OUTDIR=out
SOURCES=src/main.cpp
OBJECTS=$(patsubst src/%.cpp, $(OUTDIR)/objs/%.o, $(SOURCES))
TARGET=flatland

all: create-out v8 $(TARGET)

clean: v8-clean $(TARGET)-clean

create-out:
	mkdir -p $(OUTDIR)
	mkdir -p $(OUTDIR)/objs

v8:
	make -C deps/v8 native

v8-clean:
	make -C deps/v8 clean

$(TARGET)-clean:
	rm -rf $(OUTDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OUTDIR)/$@

$(OBJECTS): out/objs/%.o : src/%.cpp
	$(CC) $(CFLAGS) $< -o $@
