#these two targets are annoying, but there was no better way.
include config.mk

all: $(CTARGET)

$(CTARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(CTARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(CTARGET) $(OBJS)

install: $(CTARGET)
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp $(AWKTARGET) $(PREFIX)/bin
	cp $(CTARGET) $(PREFIX)/bin
	cp $(AWKTARGET).1 $(PREFIX)/share/man/man1
	chmod 755 $(PREFIX)/bin/$(AWKTARGET)
	chmod 755 $(PREFIX)/bin/$(CTARGET)
	chmod 0644 $(PREFIX)/share/man/man1/$(AWKTARGET).1

uninstall:
	rm -f $(PREFIX)/$(AWKTARGET) $(PREFIX)/bin/$(CTARGET) $(PREFIX)/share/man/man1/$(AWKTARGET).1
