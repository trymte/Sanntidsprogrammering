#pragma once

#include <mutex>

#include "elev.h"
#include "network.h"
#include "fsm.h"
#include "timer.h"



void event_manager_main(int &my_elevator_ID, Queue &my_queue, Network &my_network);