
OBJS = udp_sendrec.o utilities.o network.o\
elevator.o queue.o main.o eventmanager.o fsm.o supervisor.o elev.o io.o timer.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = -lpthread -lcomedi


.PHONY: all clean

all: elevator

elevator : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o elevator

network.o : network.h network.cpp queue.h supervisor.h
	$(CC) $(CFLAGS) network.cpp

elev.o : elev.c elev.h utilities.h
	$(CC) $(CFLAGS) elev.c

io.o : io.c io.h

timer.o : timer.c timer.h

elevator.o : elevator.h elevator.cpp udp_sendrec.h utilities.h
	$(CC) $(CFLAGS) elevator.cpp

fsm.o : fsm.cpp fsm.h queue.h
	$(CC) $(CFLAGS) fsm.cpp

supervisor.o : supervisor.cpp supervisor.h queue.h
	$(CC) $(CFLAGS) supervisor.cpp

queue.o : queue.cpp queue.h elevator.h 
	$(CC) $(CFLAGS) queue.cpp

main.o : main.cpp eventmanager.h network.h
	$(CC) $(CFLAGS) main.cpp

eventmanager.o : eventmanager.h eventmanager.cpp elev.h network.h
	$(CC) $(CFLAGS) eventmanager.cpp

utilities.o : utilities.h utilities.cpp
	$(CC) $(CFLAGS) utilities.cpp

udp_sendrec.o : udp_sendrec.cpp udp_sendrec.h
	$(CC) $(CFLAGS) udp_sendrec.cpp

clean:
	\rm *.o elevator

.PHONY: all clean