
#ifndef SIMULATION_H
#define SIMULATION_H

#include "Queue.h"
#include "DoublyLinkedList.h"
#include "Student.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;


// class to simulate the window counters
class Simulation {

private:
    // total number of windoes
    int num_windows;
    // pointer to all the windows
    // each window is a queue of Student *
    Queue<Student *> *windows;

    // Queue to store the the students waiting (in case none of the 
    // windows is free)
    Queue<Student *> waiting;

    // list of all the students
    DoublyLinkedList<Student *> all_students;

    // array to store the idle times of all the windows
    int *window_idle_time;


public:
    Simulation();
    Simulation(const char *filename);

    ~Simulation();

    // starts the given simulation
    void start(ifstream &infile);

    // Given a student, checks if any window is free
    // if window is free, student goes to that window and true if returned
    // returns fale otherwise
    bool go_to_window(Student *s);

    // given the current time, process the students present in each window
    // (process for 1 second only)
    void update_windows(int current);

    // given current time, checks all the students waiting in the waiting queue
    // if any window is empty, assigns the student to that window
    void fill_windows(int current);

    // display the final stats (mean, median)
    void display_stats(int current);

    // returns true if all windows are engages
    // returns false otherwise
    bool is_window_engaged();

    // displays all the windows
    // used for testing
    void display_windows();


};

// insertion sort algorithm
void my_sort(int *arr, int size);


#endif