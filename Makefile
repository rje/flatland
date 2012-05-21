
CC=clang++
IFLAGS=-Ideps/v8/include
CFLAGS=-c -Wall $(IFLAGS)
OUTDIR=out
LDFLAGS=-L$(OUTDIR)/libs -lv8_base -lv8_snapshot
SOURCES=src/main.cpp
OBJECTS=$(patsubst src/%.cpp, $(OUTDIR)/objs/%.o, $(SOURCES))
TARGET=flatland

all: create-out $(TARGET)

clean: v8-clean $(TARGET)-clean

create-out:
	mkdir -p $(OUTDIR)
	mkdir -p $(OUTDIR)/objs
	mkdir -p $(OUTDIR)/libs

dependencies:
	$(MAKE) -C deps/v8 dependencies

v8:
	make -C deps/v8 native
	cp deps/v8/out/native/*.a $(OUTDIR)/libs

v8-clean:
	make -C deps/v8 clean

$(TARGET)-clean:
	rm -rf $(OUTDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OUTDIR)/$@

$(OBJECTS): out/objs/%.o : src/%.cpp v8
	$(CC) $(CFLAGS) $< -o $@
