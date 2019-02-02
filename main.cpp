#include "exercise01.hpp"
#include "exercise02.hpp"
#include "exercise03.hpp"

int main()
{
    try
    {
        //run01();
        //run02();
        run03();
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    catch (int e)
    {
        cerr << e << endl;
    }
}
