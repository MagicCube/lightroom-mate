#include "LRMServer.h"

#include "LRMServerCallbacks.h"

LRMServer::LRMServer() {
  _bleServer = BLEDevice::createServer();
  _bleServer->setCallbacks(new LRMServerCallbacks(this));
  _midiService = new MIDIService(this);
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

  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  Serial.println("BLE Advertising is now started.");
}

BLEService *LRMServer::createBLEService(String uuid) {
  return _bleServer->createService(BLEUUID(uuid.c_str()));
}
