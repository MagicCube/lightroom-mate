#include "LRMServerCallback.h"

#include "LRMServer.h"

LRMServerCallbacks::LRMServerCallbacks(LRMServer *LRMServer) {
  _lrmServer = LRMServer;
}

void LRMServerCallbacks::onConnect(BLEServer *server) {
  _lrmServer->setConnected(true);
}

void LRMServerCallbacks::onDisconnect(BLEServer *server) {
  _lrmServer->setConnected(false);
}
