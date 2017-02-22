#pragma once
#include "const_struct_def.h"
#include "queue.h"


void manage_order_matrix(std::vector<Elevator> &elevators);
void manage_completed_order(Elevator &elevator);
void manage_incomplete_order(Elevator &elevator);