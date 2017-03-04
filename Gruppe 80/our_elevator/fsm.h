#include "queue.h"

void fsm_execute_order(Elevator &my_elevator, Queue &my_queue, Order &order);

void fsm_on_floor_arrival(Elevator &my_elevator,Queue &my_queue, int current_floor);

void fsm_on_door_timeout(Elevator &my_elevator,Queue &my_queue);