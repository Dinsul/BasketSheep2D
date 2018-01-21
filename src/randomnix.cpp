#include "randomnix.h"

RandomNix::RandomNix()
{
    _devRandom = fopen(URANDOM_PATH, "r");

    if (!_devRandom)
    {
        fprintf(stderr, "Can not open file\n");
    }
}

RandomNix::~RandomNix()
{
    fclose(_devRandom);
}

int RandomNix::getRandom()
{
    int retVal;

    fread(&retVal, sizeof(int), 1, _devRandom);

    return retVal;
}

int RandomNix::getRandomS()
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

