#ifndef RANDOMNIX_H
#define RANDOMNIX_H

#include <cstdio>

#define URANDOM_PATH "/dev/urandom"

class RandomNix
{
public:
    RandomNix();
    ~RandomNix();

    int getRandom();

    static int getRandomS();

private:
    FILE *_devRandom;
};

#endif // RANDOMNIX_H
