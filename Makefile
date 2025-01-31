default: build

build:
	gcc keeloq.c -c

test:build
	gcc test.c keeloq.o -o test -lcunit
	./test

clean:
	rm *.o test
