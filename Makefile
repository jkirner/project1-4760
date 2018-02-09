CC = gcc
CFLAGS = -g
TARGET = proc_fan
OBJS = runsim.o
$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
runsim.o: runsim.c
	$(CC) $(CFLAGS) -c runsim.c
clean:
	/bin/rm -f *.o $(TARGET)
CC = gcc
CFLAGS = -g
TARGET = testsim
OBJS = testsim.o
$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
testsim.o: testsim.c
	$(CC) $(CFLAGS) -c testsim.c
clean:
	/bin/rm -f *.o $(TARGET)
