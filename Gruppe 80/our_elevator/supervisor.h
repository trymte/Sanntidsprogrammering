#pragma once
#include "const_struct_def.h"
#include "queue.h"


void sv_manage_order_matrix(std::vector<Elevator> &elevators);
void sv_manage_completed_order(Elevator &elevator);
void sv_manage_incomplete_order(Elevator &elevator);