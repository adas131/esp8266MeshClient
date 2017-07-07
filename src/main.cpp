//************************************************************
// this is a simple example that uses the painlessMesh library to
// setup a node that logs to a central logging node
// The logServer example shows how to configure the central logging nodes
//************************************************************
#include "lmf/def.h"
#include "lmf/const.h"
#include "sequence.h"
#include "mesh.h"
#include "body.h"

int test[] = {
    0, 1, 2, 3, 65535, -1};
unsigned int test2 = 166;
Body::Body(int pin, int *sequence)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _sequence = sequence;
}

void Body::run()
{
    if ((millis() - startTime) < *(_sequence + seqPtr))
    {
        return;
    }

    seqPtr++;
    // Serial.printf("%d [RUN] pin:%d sequence:%d\n", millis() _pin, *(_sequence + i));

    // do
    // {
    //     Serial.printf("%d [RUN] pin:%d sequence:%d\n", millis() _pin, *(_sequence + i));
    // } while (*(++i + _sequence) != -1);
}

Body hand(0, &test[0]);
void serialLoop();

void setup()
{
    wdt_disable();
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println();
    Serial.println("[INIT] client");
    meshInit();
    wdt_enable(2000);
    ESP.wdtFeed();
}

void loop()
{
    ESP.wdtFeed();
    mesh.update();
    serialLoop();
    if (f_started)
    {
        hand.run();
    }
}

void serialLoop()
{
    while (Serial.available())
    {
        char inChar = Serial.read();
        serialString += inChar;

        if (inChar == '\n')
        {                        // truncate and parse Json
            if (logServerId > 0) // If we don't know the logServer yet
                mesh.sendSingle(logServerId, serialString);

            serialString = "";
            break;
        }
    }
}