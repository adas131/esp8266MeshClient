#include "lmf/ext_def.h"
#include "lmf/const.h"
#include "mesh.h"

size_t logServerId;

void meshInit();
void receivedCallback(uint32_t from, String &msg);
void newConnectionCallback(size_t nodeId);
void dropConnectionCallback(size_t nodeId);

void meshInit()
{
    mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION); // set before init() so that you can see startup messages

    mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, STA_AP, AUTH_OPEN, 2);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onDroppedConnection(&dropConnectionCallback);
}

void newConnectionCallback(size_t nodeId)
{
    Serial.printf("Connection establish %u\n", nodeId);
}

void dropConnectionCallback(size_t nodeId)
{
    Serial.printf("Connection break %u\n", nodeId);
}

void receivedCallback(uint32_t from, String &msg)
{
    Serial.printf("%u logClient: Received from %u msg=%s\n", millis(), from, msg.c_str());

    // Saving logServer
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(msg);
    if (root.containsKey("topic"))
    {
        if (String("logServer").equals(root["topic"].as<String>()))
        {
            // check for on: true or false
            if (!logServerId && root["nodeId"])
            {
                Serial.println("node server found");
                digitalWrite(LED, true);
                if (!f_started)
                {
                    startTime = millis();
                    f_started = true;
                }
            }

            logServerId = root["nodeId"];
            // Serial.printf("logServer detected!!!\n");
        }
        // Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
    }
}