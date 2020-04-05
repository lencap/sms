TARGET := smsclic
VERSION := 1.1.1

.PHONY: release install clean

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

LDFLAGS = -lcurl

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(LDFLAGS)

release:
	tar czf $(TARGET)-$(VERSION).tar.gz $(TARGET)
	shasum -a 256 $(TARGET)-$(VERSION).tar.gz

install:
	install $(TARGET) /usr/local/bin/$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET)*.gz $(OBJS)
