CC=gcc
DEPS = fuzz.h

make: fuzzer.o lists.o
	$(CC) -o fuzzer fuzzer.o lists.o -pthread

fuzzer.o: fuzzer.c fuzzer.h ../lists.h 
	$(CC) -c fuzzer.c
	
lists.o: ../lists.c ../lists.h
	$(CC) -c ../lists.c

clean:
	rm *.o fuzzer
