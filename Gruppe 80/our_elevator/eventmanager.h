#pragma once

#include <mutex>

#include "elev.h"
#include "network.h"
#include "fsm.h"




void event_manager_main(Elevator *my_elevator, Queue &my_queue, Network &my_network);