CC=g++
CFLAGS=-c -g -O2 -Wall -Wextra
LDFLAGS=-lstdc++
EXECUTABLE=bhpatch

all: bhpatch

bhpatch: BHPatch.o Logger.o
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) BHPatch.o Logger.o

BHPatch.o: bhpatch.cpp logger.o
	$(CC) $(CFLAGS) BHPatch.cpp

Logger.o: logger.cpp
	$(CC) $(CFLAGS) Logger.cpp

clean:
	rm -f *.o bhpatch
