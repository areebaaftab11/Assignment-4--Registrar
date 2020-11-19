
#include "Student.h"


Student::Student(int arrival_time, int window_time) {
    this->arrival_time = arrival_time;
    this->total_window_time = window_time;
    remaining_window_time = window_time;
}


// returns the waiting time 
int Student::get_wait_time() {
    return completion_time - arrival_time - total_window_time;    
}

void Student::display() {
    cout << "Arrival: " << arrival_time << ", Completion: " << completion_time 
         << ", remaining_window_time: " << remaining_window_time 
         << ", Waiting time: " << get_wait_time() << endl;
}