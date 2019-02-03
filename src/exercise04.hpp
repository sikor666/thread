#pragma once

#include "bank_account.hpp"

void run04()
{
    bank_account account;

    bank_account account1(1000, "Alice");
    bank_account account2(2000, "Bob");

    thread thread1{ &bank_account::transfer, &account,
        ref(account1), ref(account2), 800 };

    this_thread::sleep_for(chrono::milliseconds(300));

    thread thread2{ &bank_account::transfer, &account,
        ref(account2), ref(account1), 800 };

    thread1.join();
    thread2.join();
}