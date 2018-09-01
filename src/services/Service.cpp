#include "Service.h"

#include "../server/LRMServer.h"

Service::Service(LRMServer *server, String serviceUUID) {
  _server = server;
  _bleService = _server->createBLEService(serviceUUID);
}

void Service::begin() {
  _bleService->start();
}

BLECharacteristic *Service::createCharacteristic(String uuid, uint32_t properties) {
  return _bleService->createCharacteristic(BLEUUID(uuid.c_str()), properties);
}
