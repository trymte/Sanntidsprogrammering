#pragma once

#include <mutex>

#include "driver/elev.h"
#include "queue.h" //queue inkluderer elevator.h, så treng ikkje dobbel inklude her. har optimalisert inkluderingå vår i alle our_elevator filer

void event_manager_main(Elevator &my_elevator, Queue &my_queue, Network &my_network);