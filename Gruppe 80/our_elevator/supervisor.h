#pragma once
#include "queue.h"

void sv_manage_order_matrix(std::vector<Elevator*> elevators, int elevator_ID);

void sv_manage_completed_order(Elevator* elevator);