TARGET=keeloq

default: run-test

build:
	gcc keeloq.c -c

test:build
	gcc test.c $(TARGET).o -o $(TARGET)

run-test:test
	./$(TARGET)
clean:
	rm $(TARGET) $(TARGET).o
