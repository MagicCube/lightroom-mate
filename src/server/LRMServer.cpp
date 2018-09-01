#include "LRMServer.h"

#include "LRMServerCallback.h"

LRMServer::LRMServer() {
}

MIDIService *LRMServer::getMIDIService() {
  return _midiService;
}

bool LRMServer::isConnected() {
  return _connected;
}
void LRMServer::setConnected(bool connected) {
  if (_connected != connected) {
    _connected = connected;
    if (_connected) {
      Serial.println("BLE client is now connected.");
    } else {
      Serial.println("BLE client is now disconnected.");
    }
  }
}

void LRMServer::begin() {
  Serial.println("Initializing MIDI Server...");

  _bleServer = BLEDevice::createServer();
  _bleServer->setCallbacks(new LRMServerCallbacks(this));

  _midiService = new MIDIService(this);
  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  Serial.println("BLE Advertising is now started.");
}

BLEService *LRMServer::createBLEService(String uuid) {
  return _bleServer->createService(BLEUUID(uuid.c_str()));
}
