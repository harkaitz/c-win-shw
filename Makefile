CC32   =i686-w64-mingw32-gcc
CC64   =x86_64-w64-mingw32-gcc
CFLAGS =-Wall
PROGS  =
all:

ifneq ($(CC64),)
all: x64/shw.exe
x64/shw.exe : shw.c
	$(CC64) $(CFLAGS) -o $@ $<
endif
ifneq ($(CC32),)
all: x32/shw.exe
x32/shw.exe : shw.c
	$(CC32) $(CFLAGS) -o $@ $<
endif
install:
clean:
	rm -f x64/shw.exe x32/shw.exe

## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-win-shw
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-win-shw
endif
## -- license --
