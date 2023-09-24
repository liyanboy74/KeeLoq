TARGET=keeloq

default: build

build:
	gcc keeloq.c -c

test:build
	gcc test.c $(TARGET).o -o $(TARGET)
	./$(TARGET)

clean:
	rm $(TARGET) $(TARGET).o
