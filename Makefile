TARGET=keeloq

default: build run

build:
	gcc main.c keeloq.c -o $(TARGET)
run:
	$(TARGET)
clean:
	rm $(TARGET)
