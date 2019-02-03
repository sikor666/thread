#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <thread>

using namespace std;

class bank_account
{
public:
    bank_account() = default;
    bank_account(bank_account& const) = delete;
    bank_account& operator=(bank_account& const) = delete;

    bank_account(double balance_, string name_)
        : balance{ balance_ }, name{ name_ } {}

    void withdraw(double amount) {
        lock_guard<mutex> lock(m);
        balance += amount;
    }

    void deposite(double amount) {
        lock_guard<mutex> lock(m);
        balance += amount;
    }

    void transfer(bank_account& from, bank_account& to, double amount) {
        lock_guard<mutex> lock1(from.m);
        cout << "lock for " << from.name << " account acquire by "
             << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));

        cout << "waiting to acquire lock for " << to.name << " account by "
             << this_thread::get_id() << endl;
        lock_guard<mutex> lock2(to.m);

        from.balance -= amount;
        to.balance += amount;

        cout << "tranfert to: " << to.name << "\tfrom: " << from.name << " end\n";
    }

private:
    double balance;
    string name;
    mutex m;
};