#include "lmf/ext_def.h"
#include "body.h"

Body::Body(int pin, long *sequence)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _sequence = sequence;
    _seqPtr = 0;
}

void Body::run()
{
    long *ptr = _sequence + _seqPtr * 2;

    if(*ptr == -1) {
        return;
    }
    // if ((millis() - startTime) < *ptr)
    // {
    //     return;
    // }

    Serial.printf("%d [RUN] pin:%d *sequence:%d\n", millis(), _pin, *(ptr + 1));
    _seqPtr ++;

    // do
    // {
    //     Serial.printf("%d [RUN] pin:%d sequence:%d\n", millis() _pin, *(_sequence + i));
    // } while (*(++i + _sequence) != -1);
}