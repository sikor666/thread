#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

#include "scoped_thread.hpp"

using namespace std;

namespace e3
{

// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(chrono::microseconds us, bool& run)
{
    auto start = chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
        this_thread::yield();
    } while (chrono::high_resolution_clock::now() < end && run);
}

void clean(bool& run)
{
    little_sleep(chrono::milliseconds(16000), run);

    printf("%d: Clean\n", this_thread::get_id());
}

void fullSpeedAhead()
{
    printf("%d: Full speed ahead\n", this_thread::get_id());
}

void stopTheEngine()
{
    printf("%d: Stop the engine\n", this_thread::get_id());
}

void weAreUnderAttack()
{
    printf("%d: We are under attack\n", this_thread::get_id());
}

}

void run03()
{
    int c;
    bool run = true;
    auto hc = thread::hardware_concurrency();

    cout << "Hardware threads: " << hc << endl;

    do
    {
        cin >> c;

        thread command;

        switch (c)
        {
        case 1:
        {
            vector<thread> commands(hc ? hc : 2);
            for_each(begin(commands), end(commands), [&](thread& t) {
                t = thread{ e3::clean, ref(run) };
            });
            for_each(begin(commands), end(commands), mem_fn(&thread::detach));
            break;
        }
        case 2:
            command = thread{ e3::fullSpeedAhead };
            command.detach();
            break;
        case 3:
            command = thread{ e3::stopTheEngine };
            command.detach();
            break;
        case 4:
        {
            scoped_thread scoped_command{ thread{ e3::weAreUnderAttack } };
            throw 666;
            break;
        }
        case 5:
        {
            scoped_thread scoped_command{ {} };
            break;
        }
        case 6:
        {
            vector<thread> commands;
            commands.emplace_back(thread{ e3::stopTheEngine });
            commands.emplace_back(thread{ e3::clean, ref(run) });
            commands.emplace_back(thread{ e3::weAreUnderAttack });
            commands.emplace_back(thread{ e3::fullSpeedAhead });

            for_each(begin(commands), end(commands), mem_fn(&thread::detach));
            break;
        }
        case 100:
            run = false;
            break;
        default:
            break;
        }
    }
    while (run);

    printf("%d: Ahoy\n", this_thread::get_id());

    auto start = std::chrono::high_resolution_clock::now();

    run = true;
    e3::little_sleep(std::chrono::microseconds(3000), run);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    printf("Waited for %d microseconds\n",
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
}
