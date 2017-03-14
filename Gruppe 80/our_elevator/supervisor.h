#pragma once
#include "queue.h"

// Takes in all elevator objects with order matrices, assigns orders to online 
// elevators who have the out_of_order bool equal to false (condition == true)
void sv_manage_order_matrix(std::vector<Elevator*> elevators, int elevator_ID);


// Case 1: Takes in the elevator who completed an order and removes it 
// Case 2: Takes in a SLAVE elevator who are offline such that its orders have to be reset
// 			and given to others
void sv_manage_incompleted_and_completed_orders(Elevator* elevator);