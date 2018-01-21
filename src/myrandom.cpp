#include "myrandom.h"

MyRandom::MyRandom()
{
    _devRandom = fopen(URANDOM_PATH, "r");

    if (!_devRandom)
    {
        fprintf(stderr, "Can not open file\n");
    }
}

MyRandom::~MyRandom()
{
    fclose(_devRandom);
}

int MyRandom::getRandom()
{
    int retVal;

    fread(&retVal, sizeof(int), 1, _devRandom);

    return retVal;
}

int MyRandom::getRandomS()
{
    FILE *devRandom;
    int retVal;

    devRandom = fopen(URANDOM_PATH, "r");

    if (!devRandom)
    {
        fprintf(stderr, "Can not open file\n");
        return 0;
    }

    fread(&retVal, sizeof(int), 1, devRandom);

    fclose(devRandom);

    return retVal;
}

