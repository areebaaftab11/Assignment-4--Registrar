
#include "Simulation.h"


Simulation::Simulation() {
    num_windows = 0;
    windows = NULL;
}


Simulation::Simulation(const char *filename) {

    num_windows = 0;
    windows = NULL;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    infile >> num_windows;
    // allocate each window
    // each window is a queue which stores the Student * pointer
    // each window has only 1 student at a time
    windows = new Queue<Student *>[num_windows];

    window_idle_time = new int[num_windows];
    // initialize window idle time as 0 for each window
    for (int i = 0; i < num_windows; i++)
        window_idle_time[i] = 0;

    start(infile);
}

Simulation::~Simulation() {
    if (windows != NULL)
        delete [] windows;

    if (window_idle_time != NULL)
        delete [] window_idle_time;

    // free all the student pointers
    for (int i = 0; i < all_students.get_size(); i++) {
        Student *s = all_students.get_data(i);
        if (s != NULL)
            delete s;
    }
}

// starts the given simulation
void Simulation::start(ifstream &infile) {
    int arrival, num_students, window_time;

    // add all students to waiting queue
    while(infile >> arrival) {
        infile >> num_students;
        for (int i = 0; i < num_students; i++) {
            infile >> window_time;
            Student *s = new Student(arrival, window_time);
            waiting.enqueue(s);
            all_students.insert_end(s);
        }
    }

    // remove students from waiting queue and add them to windows
    // until waiting queue is empty
    int current = 0;        // current time in minutes
    while (!waiting.is_empty()) {
    
        update_windows(current);
        fill_windows(current);

        current += 1;
    }

    // process each window until all windows are emtpy
    while (is_window_engaged()) {
        update_windows(current); 
        current += 1;
    }

    // display the final stats
    display_stats(current);
}


// returns true if all windows are engages
// returns false otherwise
bool Simulation::is_window_engaged() {
    for (int i = 0; i < num_windows; i++) {
        if (!windows[i].is_empty())
            return true;
    }
    return false;
}


// displays all the windows
// used for testing
void Simulation::display_windows() {
    cout << "num_windows " << num_windows << endl;
    for (int i = 0; i < num_windows; i++) {
        cout << "window no: " << i << endl;
        if (!windows[i].is_empty())
            windows[i].display();
    }
}

// given the current time, process the students present in each window
// (process for 1 second only)
void Simulation::update_windows(int current) {
    for (int i = 0; i < num_windows; i++) {
        // if window is not empty
        if (!windows[i].is_empty()) {
            Student *s = windows[i].peek();
            s->remaining_window_time -= 1;
            // if student has finished his work
            if (s->remaining_window_time <= 0) {
                s->completion_time = current;
                windows[i].dequeue();
            }
        }
        // if window is empty
        else
            window_idle_time[i] += 1;
    }
}

// given current time, checks all the students waiting in the waiting queue
// if any window is empty, assigns the student to that window
void Simulation::fill_windows(int current) {
    while (!waiting.is_empty()) {
        Student *s = waiting.peek();
        // if the student has arrived
        if (s->arrival_time <= current) {
            bool success = go_to_window(s);
            if (!success)
                break;
            else {
                waiting.dequeue();    
            }
        }
        else
            break;
    }    
}


// Given a student, checks if any window is free
// if window is free, student goes to that window and true if returned
// returns fale otherwise
bool Simulation::go_to_window(Student *s) {
    for (int i = 0; i < num_windows; i++) {
        if (windows[i].is_empty()) {
            windows[i].enqueue(s);
            return true;
        }
    }
    return false;
}


// display the final stats (mean, median)
void Simulation::display_stats(int current) {

    int *all_waiting_times = new int[all_students.get_size()]; 
    double mean_waiting_time = 0;
    int longest_waiting_time = 0;
    int over_10_mins = 0;

    for (int i = 0; i < all_students.get_size(); i++) {
        Student *s = all_students.get_data(i);
        mean_waiting_time += s->get_wait_time();
        all_waiting_times[i] = s->get_wait_time();

        if (all_waiting_times[i] > longest_waiting_time)
            longest_waiting_time = all_waiting_times[i];

        if (all_waiting_times[i] > 10)
            over_10_mins += 1;
    }

    my_sort(all_waiting_times, all_students.get_size());
    mean_waiting_time /= all_students.get_size();

    double median;
    if (all_students.get_size() % 2 == 0) {
        median = (all_waiting_times[all_students.get_size() / 2] +
                all_waiting_times[all_students.get_size() / 2 + 1]) / 2;
    }
    else {
        median = all_waiting_times[all_students.get_size() / 2];
    }



    double mean_idle_time = 0;
    int longest_idle_time = 0;
    int over_5_mins_idle = 0;
    for (int i = 0; i < num_windows; i++) {
        mean_idle_time += window_idle_time[i];

        if (window_idle_time[i] > longest_idle_time)
            longest_idle_time = window_idle_time[i];

        if (window_idle_time[i] > 5)
            over_5_mins_idle += 1;
    }

    mean_idle_time /= num_windows;

    cout << "For time 0 - " << current << " minutes:\n" << endl;
    cout << "Mean student wait time: " << mean_waiting_time << endl;
    cout << "Median student wait time: " << median << endl;
    cout << "Longest student wait time: " << longest_waiting_time << endl;
    cout << "Number of students waiting over 10 minutes: " << over_10_mins << endl;
    cout << "Mean window idle time: " << mean_idle_time << endl;
    cout << "Longest window idle time: " << longest_idle_time << endl;
    cout << "Number of windows idle for over 5 minutes: " << over_5_mins_idle << endl;

    if (all_waiting_times != NULL)
        delete [] all_waiting_times;

}


// insertion sort algo
// sorts the given array in increasing order
void my_sort(int *arr, int size) {
    for (int i = 1; i < size; i++) {  
        int key = arr[i];  
        
        int j;
        for (j = i-1; j >= 0 && arr[j] > key; j++) {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}