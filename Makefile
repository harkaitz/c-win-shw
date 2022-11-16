CC32     =i686-w64-mingw32-gcc
CC64     =x86_64-w64-mingw32-gcc
CFLAGS   =-Wall
PROGRAMS =x64/shw.exe x32/shw.exe
all: $(PROGRAMS)
install:
	@true
clean:
	rm -f $(PROGRAMS)


ifneq ($(CC64),)
x64/shw.exe : shw.c
	$(CC64) $(CFLAGS) -o $@ $<
endif
ifneq ($(CC32),)
x32/shw.exe : shw.c
	$(CC32) $(CFLAGS) -o $@ $<
endif
