#include <iostream>

typedef enum tag_elev_lamp_type { 
    BUTTON_CALL_UP = 0,
    BUTTON_CALL_DOWN = 1,
    BUTTON_COMMAND = 2
} elev_button_type_t;


int main(){
	
	elev_button_type_t test_enum;
	test_enum = static_cast<elev_button_type_t>( 2 );
	




}