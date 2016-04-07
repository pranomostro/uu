#these three targets are annoying, but there was no better way.
include config.mk

all: $(BIN) config.h

fnuu: fnuu.c deps/murmurhash/murmurhash.c
	$(CC) $(CFLAGS) $^ -o $@

bauu: bauu.c deps/murmurhash/murmurhash.c
	$(CC) $(CFLAGS) $^ -o $@ $

clean:
	rm -rf $(BIN) $(OBJ)

install: $(BIN)
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp $(AWKTARGET) $(PREFIX)/bin
	cp $(BIN) $(PREFIX)/bin
	cp $(AWKTARGET).1 $(PREFIX)/share/man/man1
	chmod 755 $(PREFIX)/bin/$(AWKTARGET)
	chmod 755 $(PREFIX)/bin/$(CTARGET)
	chmod 644 $(PREFIX)/share/man/man1/$(AWKTARGET).1

uninstall:
	rm -f $(PREFIX)/bin/$(AWKTARGET) $(PREFIX)/share/man/man1/$(AWKTARGET).1
	cd $(PREFIX)/bin && rm -f $(BIN)
