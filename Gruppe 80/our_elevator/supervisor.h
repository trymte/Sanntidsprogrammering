#pragma once
#include "utilities.h"
#include "queue.h"


void sv_manage_order_matrix(std::vector<Elevator> &elevators, int master_elevator_ID);
void sv_manage_completed_order(Elevator &elevator, int master_elevator_ID);
void sv_manage_incomplete_order(Elevator &elevator, int master_elevator_ID);

