//************************************************************
// this is a simple example that uses the painlessMesh library to
// setup a node that logs to a central logging node
// The logServer example shows how to configure the central logging nodes
//************************************************************
#include <painlessMesh.h>

#define MESH_PREFIX "whateverYouLike"
#define MESH_PASSWORD "somethingSneaky"
#define MESH_PORT 5555
#define LED D4

void receivedCallback(uint32_t from, String &msg);
void newConnectionCallback(size_t nodeId);
void dropConnectionCallback(size_t nodeId);
void serialLoop();

painlessMesh mesh;
String serialString;

size_t logServerId = 0;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    // mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION); // set before init() so that you can see startup messages

    mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, STA_AP, AUTH_WPA2_PSK, 6);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onDroppedConnection(&dropConnectionCallback);
}

void loop()
{
    mesh.update();
    serialLoop();
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
    Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

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
            }

            logServerId = root["nodeId"];
            // Serial.printf("logServer detected!!!\n");
        }
        // Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
    }
}

void serialLoop()
{
    while (Serial.available())
    {
        char inChar = Serial.read();
        serialString += inChar;

        if (inChar == '\n')
        {                         // truncate and parse Json
            if (logServerId == 0) // If we don't know the logServer yet
                mesh.sendBroadcast(serialString);
            else
                mesh.sendSingle(logServerId, serialString);

            serialString = "";
            break;
        }
    }
}