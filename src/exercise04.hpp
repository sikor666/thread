#pragma once

#include "bank_account.hpp"

mutex m1;
mutex m2;
mutex m3;

recursive_mutex mr;

void m1_first_m2_second()
{
/*
 * Deadlock
 *
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "thread " << this_thread::get_id()
         << " has acquired lock for m1 mutex, it's wait for m2" << endl;

    lock_guard<mutex> lock2(m2);
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m2 mutex, it's wait for m1" << endl;
*/
}

void m2_first_m1_second()
{
/*
 * Deadlock
 *
    lock_guard<mutex> lock2(m2);
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m2 mutex, it's wait for m1" << endl;

    lock_guard<mutex> lock1(m1);
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m1 mutex, it's wait for m2" << endl;
*/
}

void thread_fun5(thread& t)
{
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "thread " << this_thread::get_id()
         << " wait for thred " << t.get_id() << endl;
/*
 * Deadlock
 *
    t.join(); cout << "thread6.join()" << endl;
*/

    t.detach(); cout << "thread6.detach()" << endl;
}

void thread_fun6(thread& t)
{
    this_thread::sleep_for(chrono::milliseconds(800));
    cout << "thread " << this_thread::get_id()
        << " wait for thred " << t.get_id() << endl;

/*
 * Deadlock
 *
    t.join(); cout << "thread5.join()" << endl;
*/

    t.detach(); cout << "thread5.detach()" << endl;
}

void recursive_function(int& counter)
{
    lock_guard<mutex> lock(recursive_mutex);

    auto id = this_thread::get_id();
    printf("Recursive function has couner: %d in thread %d\n", counter, id);

    if (--counter <= 0) return;

    this_thread::sleep_for(chrono::milliseconds(300));

    recursive_function(counter);
}

void x_operations()
{
    cout << "this is some operations\n";
}

void y_operations()
{
    cout << "this is some other operations\n";
}

unique_lock<mutex> get_lock()
{
    unique_lock<mutex> lock(m3);
    x_operations();
    return lock;
}

void run04()
{
    bank_account account;

    bank_account account1(1000, "Alice");
    bank_account account2(2000, "Bob");

    //deadlock 1
    thread thread1{ &bank_account::transfer, &account,
        ref(account1), ref(account2), 800 };

    this_thread::sleep_for(chrono::milliseconds(300));

    thread thread2{ &bank_account::transfer, &account,
        ref(account2), ref(account1), 800 };

    this_thread::sleep_for(chrono::milliseconds(4000));

    //deadlock 2
    thread thread3{ m1_first_m2_second };
    thread thread4{ m2_first_m1_second };

    this_thread::sleep_for(chrono::milliseconds(1000));

    //deadlock 3
    thread thread5;
    thread thread6;

    thread5 = thread{ thread_fun5, ref(thread6) };
    thread6 = thread{ thread_fun6, ref(thread5) };

    this_thread::sleep_for(chrono::milliseconds(1000));

    //deadlock 4 and crash
    int counter = 4;
    thread thread7{ recursive_function, ref(counter) };
    thread thread8{ recursive_function, ref(counter) };

    this_thread::sleep_for(chrono::milliseconds(1000));

    //move unique_lock
    unique_lock<mutex> lock(get_lock());
    y_operations();

    thread1.join(); cout << "thread1.join()" << endl;
    thread2.join(); cout << "thread2.join()" << endl;
    thread3.join(); cout << "thread3.join()" << endl;
    thread4.join(); cout << "thread4.join()" << endl;

    thread7.join(); cout << "thread7.join()" << endl;
    thread8.join(); cout << "thread8.join()" << endl;

    cout << "End of examples about deadlocks" << endl;
}