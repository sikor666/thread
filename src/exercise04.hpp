#pragma once

#include "bank_account.hpp"

mutex m1;
mutex m2;

void m1_first_m2_second()
{
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "thread " << this_thread::get_id()
         << " has acquired lock for m1 mutex, it's wait for m2" << endl;

    lock_guard<mutex> lock2(m2);
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m2 mutex, it's wait for m1" << endl;
}

void m2_first_m1_second()
{
    lock_guard<mutex> lock2(m2);
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m2 mutex, it's wait for m1" << endl;

    lock_guard<mutex> lock1(m1);
    cout << "thread " << this_thread::get_id()
        << " has acquired lock for m1 mutex, it's wait for m2" << endl;
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

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
}