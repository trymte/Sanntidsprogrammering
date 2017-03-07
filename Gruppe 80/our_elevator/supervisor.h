#pragma once
#include "utilities.h"
#include "queue.h"


void sv_manage_order_matrix(std::vector<Elevator> *elevators);
void sv_manage_completed_order(int &my_elevator_ID, std::vector<Elevator>* elevators);