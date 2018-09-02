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
      Serial.println("[SERVER]\tBLE client is now connected.");
    } else {
      Serial.println("[SERVER]\tBLE client is now disconnected.");
    }
  }
}

void LRMServer::begin() {
  Serial.println("[SERVER]\tInitializing MIDI Server...");

  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);

  Serial.println("[SERVER]\tBLE Advertising is now started.");
}

BLEService *LRMServer::createBLEService(String uuid) {
  return _bleServer->createService(BLEUUID(uuid.c_str()));
}
