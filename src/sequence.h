#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

enum
{
    NONE,
    ALL,
    UPPER,
    LOWER,
    LEFT,
    RIGHT
};

enum
{
    STOP = -1,
    OFF,
    ON,
    FLASH_50MS,
    FLASH_100MS,
    FADE_IN,
    FADE_OUT,
    FADE_INOUT,
    FADE_OUTIN
};

long handCSV[] = {
    0, OFF, 1000, ON, 2000, FLASH_50MS, 5000, OFF, -1, STOP};

long headCSV[]  = {};
#endif