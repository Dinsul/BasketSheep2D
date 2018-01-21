#ifndef MyRandom_H
#define MyRandom_H

#include <cstdio>

#define URANDOM_PATH "/dev/urandom"

class MyRandom
{
public:
    MyRandom();
    ~MyRandom();

    int getRandom();

    static int getRandomS();

private:
    FILE *_devRandom;
};

#endif // MyRandom_H
