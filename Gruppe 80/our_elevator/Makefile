
OBJS = udp_sendrec.o const_struct_def.o network.o elevator.o queue.o main.o eventmanager.o fsm.o  
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = -pthread


.PHONY: all clean

all: test_heis

test_heis : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o test_heis

network.o : network.h network.cpp elevator.h const_struct_def.h
	$(CC) $(CFLAGS) network.cpp

elevator.o : elevator.h elevator.cpp const_struct_def.h
	$(CC) $(CFLAGS) elevator.cpp

queue.o : queue.cpp queue.h elevator.h
	$(CC) $(CFLAGS) queue.cpp

main.o : network.h queue.h const_struct_def.h elevator.h
	$(CC) $(CFLAGS) main.cpp

const_struct_def.o : const_struct_def.h const_struct_def.cpp
	$(CC) $(CFLAGS) const_struct_def.cpp

udp_sendrec.o : udp_sendrec.cpp udp_sendrec.h
	$(CC) $(CFLAGS) udp_sendrec.cpp

clean:
	\rm *.o test_heis

.PHONY: all clean