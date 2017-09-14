#include <cstdio>
#include "compute.h"


int main(int argc, char *argv[])
{
    std::function<int(int)> closure = [](int n) -> int { return 5 * n; };

    ComputeCacher cacher(closure);
}