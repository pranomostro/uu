include config.mk

all: $(BIN)

$(BIN): $(OBJ)
$(OBJ): $(CONF)

.o:
	$(CC) $(LDFLAGS) -o $@ $< $(NBO)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BT) $(OBJ)

install: all
	mkdir -p $(PREFIX)/bin/
	cp $(BIN) $(PREFIX)/bin/
	cp $(MAN) $(PREFIX)/share/man/man1/
	cd $(PREFIX)/bin/ && chmod 755 $(BIN)
	cd $(PREFIX)/share/man/man1/ && chmod 644 $(MAN)

uninstall:
	cd $(PREFIX)/bin/ && rm -f $(BIN)
	cd $(PREFIX)/share/man/man1/ && rm -f $(MAN)

.PHONY: all clean install uninstall
