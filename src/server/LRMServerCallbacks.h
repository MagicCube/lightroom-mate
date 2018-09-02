#pragma once

#include <BLEUtils.h>

class LRMServer;

class LRMServerCallbacks : public BLEServerCallbacks {
public:
  LRMServerCallbacks(LRMServer *LRMServer);

  void onConnect(BLEServer *server);
  void onDisconnect(BLEServer *server);

private:
  LRMServer *_lrmServer;
};
