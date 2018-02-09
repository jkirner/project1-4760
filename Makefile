CC = gcc
CFLAGS = -g
TARGET = wc
OBJS = runsim.o testsim.o
$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
testsim.o: testsim.c
	$(CC) $(CFLAGS) -c testsim.c
runsim.o: runsim.c
	$(CC) $(CFLAGS) -c runsim.c
clean:
	/bin/rm -f *.o $(TARGET)
