CC       =x86_64-w64-mingw32-gcc -Wall
PROGRAMS =x64/shw.exe
all: $(PROGRAMS)
install:
	@true
clean:
	rm -f $(PROGRAMS)
x64/shw.exe : shw.c
	@mkdir -p x64
	$(CC) -o $@ $< $(CFLAGS)
