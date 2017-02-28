#include <iostream>



typedef enum { 
    B_HallUp = 0,
    B_HallDown = 1,
    B_Cab = 2
} Button;



int main(){
	Button test_button = B_HallUp;
	test_button == (Button)0;
}