TARGET := smsclic
VERSION := 1.1.0

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
	./install.sh $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET)*.gz $(OBJS)
