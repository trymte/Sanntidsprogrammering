#pragma once

#include <stdlib.h>
#include <deque>
#include <string>
#include "elev.h"
#include "OrderManager.h"

typedef enum { UP, DOWN, IDLE, OPEN}state;

class Elevator{
	public:
		unsigned int elevatorOrderMatrix[N_FLOORS][N_BUTTONS];
		unsigned int costMatrix[N_FLOORS][N_BUTTONS];
		unsigned int costActiveMatrix[N_FLOORS][N_BUTTONS];
		std::deque<int> orders;
		std::deque<int> ordersOnHoldUp;
		std::deque<int> ordersOnHoldDown;
		state currentState;
		state direction;
		int identity;
		int currentFloor;
		int stateIndex;
		int directionIndex;
		int nextOrder;

		Elevator(int);
		void run();
		bool driveToFloor();
		void stopAtFloor();
		int getNextOrder();
		state getState(int);
		int getCurrentFloor();
		void addOrder(int, elev_button_type_t);
		void clearOrder();
		bool notInQue(int, std::deque<int>);
		void extendAll(std::deque<int>);
		void extendOrdersUp();
		void extendOrdersDown();
		void setDirectionState();
		void sortOrders();
		int getDirectionIndex();
		int getStateIndex();
		bool isOver(std::deque<int>);
		bool isUnder(std::deque<int>);
		bool isCurrentFloor(std::deque<int>);
		void toUp();
		void toDown();
		void toIdle();
		void toOpen();
		void printOrders(std::string, std::deque<int>);
		inline const char* toString(state);
		bool checkifOrderEmpty();
};