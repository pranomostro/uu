include config.mk

all: $(BIN) config.h

fnuu: nal.c fnuu.c deps/murmurhash/murmurhash.c
	$(CC) $(CFLAGS) $^ -o $@

bauu: bauu.c nal.c deps/murmurhash/murmurhash.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BIN) $(OBJ)

install: $(BIN)
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp $(AWKTARGET) $(BIN) $(PREFIX)/bin
	cp $(AWKTARGET).1 $(PREFIX)/share/man/man1
	cd $(PREFIX)/bin && chmod 755 $(BIN) $(AWKTARGET)
	chmod 644 $(PREFIX)/share/man/man1/$(AWKTARGET).1

uninstall:
	rm -f $(PREFIX)/share/man/man1/$(AWKTARGET).1
	cd $(PREFIX)/bin && rm -f $(BIN) $(AWKTARGET)
