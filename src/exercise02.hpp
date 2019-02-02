#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

#include "scoped_thread.hpp"

using namespace std;

void clean()
{
    std::this_thread::sleep_for(6s);

    cout << "Clean" << endl;
}

void fullSpeedAhead()
{
    cout << "Full speed ahead" << endl;
}

void stopTheEngine()
{
    cout << "Stop the engine" << endl;
}

void weAreUnderAttack()
{
    cout << "We are under attack" << endl;
}

void run02()
{
    cout << "Hardware threads: " << thread::hardware_concurrency() << endl;

    int c;

    do
    {
        cin >> c;

        thread command;

        switch (c)
        {
        case 1:
            command = thread{ clean };
            command.detach();
            break;
        case 2:
            command = thread{ fullSpeedAhead };
            command.detach();
            break;
        case 3:
            command = thread{ stopTheEngine };
            command.detach();
            break;
        case 4:
        {
            scoped_thread scoped_command{ thread{ weAreUnderAttack } };
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
            commands.emplace_back(thread{ stopTheEngine });
            commands.emplace_back(thread{ clean });
            commands.emplace_back(thread{ weAreUnderAttack });
            commands.emplace_back(thread{ fullSpeedAhead });

            for_each(begin(commands), end(commands), mem_fn(&thread::detach));
            break;
        }
        default:
            break;
        }
    }
    while (c != 100);

    cout << "Ahoy" << endl;
}
