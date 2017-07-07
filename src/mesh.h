extern size_t logServerId;

extern void meshInit();
extern void receivedCallback(uint32_t from, String &msg);
extern void newConnectionCallback(size_t nodeId);
extern void dropConnectionCallback(size_t nodeId);