#pragma once

#include <iostream>
#include <thread>

using namespace std;

void test()
{
    cout << "Hello from test" << endl;
}

void functionA()
{
    thread threadC(test);
    threadC.join();
    cout << "Hello from functionA" << endl;
}

void functionB()
{
    cout << "Hello from functionB" << endl;
}

void run01()
{
    thread threadA(functionA);
    threadA.join();
    thread threadB(functionB);
    threadB.join();

    cout << "Hello from run01" << endl;
}
