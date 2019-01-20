#include <iostream>
#include <unistd.h>

#include "timecost.hpp"

using namespace std;

void test()
{
    TIMECOST_START(__FUNCTION__);
    sleep(5);
    TIMECOST_END(__FUNCTION__);
}

void test_raii()
{
    TIMECOST_RAII(__FUNCTION__);
    sleep(5);
}

int main()
{
    test();
    test_raii();
    TIMECOST_REPORT();
    return 0;
}
