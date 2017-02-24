#include <iostream>

#include "elev.h"

int main(){
	elev_button_type_t button_type = BUTTON_CALL_UP;

	elev_set_button_lamp(button_type, 1, 1);
}

