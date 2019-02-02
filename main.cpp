#include "exercise01.hpp"
#include "exercise02.hpp"

int main()
{
    try
    {
        //run01();
        run02();
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
