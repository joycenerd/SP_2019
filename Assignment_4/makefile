CC=gcc
SOURCES=hw4_dir.c
OBJECTS=hw4_dir.o
TARGET=hw4_dir

all: $(TARGET) clean
$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -c $(SOURCES)
clean:
	rm -rf $(OBJECTS)
