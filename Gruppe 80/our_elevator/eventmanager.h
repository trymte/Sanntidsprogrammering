#pragma once

#include <mutex>

#include "driver/elev.h"
#include "elevator.h"
#include "queue.h"






void state_machine_main(Elevator &my_elevator, Queue &my_queue, Network &my_network);