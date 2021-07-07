#include <iostream>

#include "CServiceARunner.h"
#include "../Data.hh"

int main(int argc, char **argv)
{
    CServiceARunner runner(argc, argv);
    std::cout << runner.get_ior() << std::endl;
    runner.run();
    return 0;
}