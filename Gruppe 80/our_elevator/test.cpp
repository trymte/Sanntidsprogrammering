#include <vector>
#include <iostream>

using namespace std;

struct Queue_element{
	bool active_button;
	int elevator_ID;
};


typedef vector<vector <Queue_element> > 2d_array;

int main(){
	Queue_element initial;
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
	return 0;
}