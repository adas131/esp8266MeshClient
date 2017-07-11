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

Body hand(0, handCSV);
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
        { // truncate and parse Json
            if (logServerId > 0)
            { // If we don't know the logServer yet
                mesh.sendSingle(logServerId, serialString);
            }

            serialString = "";
            break;
        }
    }
}