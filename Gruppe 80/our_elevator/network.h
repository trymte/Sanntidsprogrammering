#include "queue.h"

//Bør ligge i en annen fil! Sammen med funksjonen "update_elevator() som må lages"
class Elevator{
private:
	Queue elevator_queue;
	Status elevator_status;	
public:
	Status get_elevator_status;

	void set_elevator_dir(Dirn dir);
	void set_elevator_floor(unsigned int floor);
	void set_elevator_ID(int elevator_ID);
	void set_elevator_out_of_order(bool out_of_order);
};