CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=#-lm
OUTPUT=topsecret

# targets
all: $(OUTPUT)

$(OUTPUT): topsecret.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) topsecret.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

topsecret.o: topsecret.c topsecret.h
	$(CC) $(CFLAGS) -c topsecret.c $(LDLIBS) -o topsecret.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o


