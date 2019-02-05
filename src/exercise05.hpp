#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

bool have_i_arrived = false;
int total_distance = 10;
int distance_covered = 0;

condition_variable cv;
mutex m;

void keep_moving()
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "keep moving, current distance = " << distance_covered++ << endl;

        //notify the waiting threads if the event occuress
        if (distance_covered == total_distance)
            cv.notify_one();
    }
}

void ask_driver_to_wake_you_up_at_right_time()
{
    unique_lock<mutex> lock(m);
    cv.wait(lock, []() { return distance_covered == total_distance; });
    cout << "finally i am there, distance covered = " << distance_covered << endl;
}

void run05()
{
    thread driver_thread(keep_moving);
    thread passenger_thread(ask_driver_to_wake_you_up_at_right_time);
    passenger_thread.join();
    driver_thread.join();
}
