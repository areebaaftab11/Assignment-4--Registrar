#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;


// class to store the details of a single student
class Student {

public:
    int arrival_time;           // time at which student arrives
    int completion_time;        // time at which student leaves
    int total_window_time;      // total window time required 
    int remaining_window_time;  // remaining window time

    Student() {};
    Student(int arrival_time, int window_time);
    // returns the waiting time 
    int get_wait_time();

    void display();
};



#endif