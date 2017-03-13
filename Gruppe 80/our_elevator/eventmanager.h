#pragma once

#include "elev.h"
#include "network.h"
#include "fsm.h"

void event_manager_main(Elevator *my_elevator, Network &my_network, Queue &my_queue);