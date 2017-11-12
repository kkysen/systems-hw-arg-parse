CC = gcc -ggdb -std=c99 -Wall -Werror -O3
OUT = arg_parse

util.o:
	$(CC) -c util.c

stacktrace.o:
	$(CC) -c stacktrace.c

$(OUT).o:
	$(CC) -c $(OUT).c

all: clean $(OUT).o stacktrace.o util.o
	$(CC) -o $(OUT) $(OUT).o stacktrace.o util.o

clean:
	rm -f *.o
	rm -f $(OUT)

install: clean all

run: install
	./$(OUT)

rerun: all
	./$(OUT)

valgrind: clean all
	valgrind -v --leak-check=full ./$(OUT)