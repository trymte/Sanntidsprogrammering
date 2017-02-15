#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Queue_element{
	bool active_button;
	int elevator_ID;
};

typedef enum { 
    D_Down  = -1,
    D_Stop  = 0, 
    D_Up    = 1 
} Dirn;

//typedef vector<vector <Queue_element> > 2d_array;

int main(){
	/*Queue_element initial;
	initial.active_button = 0;
	initial.elevator_ID = 1;
	2d_array matrix;
	2d_array *matrix_ptr;

	matrix.resize(4, vector<Queue_element>(3, initial));

	for(auto outer = matrix.begin(); outer != matrix.end(); outer++){
		for(auto inner = outer->begin(); inner != outer->begin(); inner++){
			cout << inner->active_button << ": " << inner->elevator_ID << ";";
		}
		cout << endl;
	}
	*/

	string text = "1 D_Stop 3 False 0 1 1 3 4 1 1";
	stringstream ss(text);
	int elevator_ID;
	int floor;
	bool out_of_order;
	Dirn dir;
	string order_matrix_string;
	ss >> elevator_ID >> static_cast<Dirn>(dir) >> floor >> out_of_order >> order_matrix_string;

	cout << "elev id: " << elevator_ID << "dir: " << dir << "floor: " << floor << "out_of_order: " << out_of_order << "order_matrix_string: " << order_matrix_string << endl;



	return 0;
}