#include "queue.h"
#include "elev.h"
#include "network.h"
#include "timer.h"

void fsm_execute_order(int &my_elevator_ID, Network &my_network, Queue &my_queue, Order &order);

bool fsm_on_floor_arrival(int &my_elevator_ID, Network &my_network ,Queue &my_queue, int current_floor);

void fsm_on_door_timeout(int &my_elevator_ID, Network &my_network, Queue &my_queue);