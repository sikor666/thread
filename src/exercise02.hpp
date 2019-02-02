#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

#include "scoped_thread.hpp"

using namespace std;

namespace e2
{

void clean()
{
    this_thread::sleep_for(6s);

    cout << this_thread::get_id() << ": Clean" << endl;
}

void fullSpeedAhead()
{
    cout << this_thread::get_id() << ": Full speed ahead" << endl;
}

void stopTheEngine()
{
    cout << this_thread::get_id() << ": Stop the engine" << endl;
}

void weAreUnderAttack()
{
    cout << this_thread::get_id() << ": We are under attack" << endl;
}

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
            command = thread{ e2::clean };
            command.detach();
            break;
        case 2:
            command = thread{ e2::fullSpeedAhead };
            command.detach();
            break;
        case 3:
            command = thread{ e2::stopTheEngine };
            command.detach();
            break;
        case 4:
        {
            scoped_thread scoped_command{ thread{ e2::weAreUnderAttack } };
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
            commands.emplace_back(thread{ e2::stopTheEngine });
            commands.emplace_back(thread{ e2::clean });
            commands.emplace_back(thread{ e2::weAreUnderAttack });
            commands.emplace_back(thread{ e2::fullSpeedAhead });

            for_each(begin(commands), end(commands), mem_fn(&thread::detach));
            break;
        }
        default:
            break;
        }
    }
    while (c != 100);

    cout << this_thread::get_id() << ": Ahoy" << endl;
}
