#include "LRMServer.h"

class LRMServerCallbacks : public BLEServerCallbacks {
public:
  LRMServerCallbacks(LRMServer *LRMServer) {
    _lrmServer = LRMServer;
  }

  void onConnect(BLEServer *server) {
    _lrmServer->setConnected(true);
  }

  void onDisconnect(BLEServer *server) {
    _lrmServer->setConnected(false);
  }

private:
  LRMServer *_lrmServer;
};


LRMServer::LRMServer() {
  auto chipId = ESP.getEfuseMac();
  // Only use the last 4 byte as ID
  _name = String("LightroomMate-" + String((uint32_t)chipId));
}

String LRMServer::getName() {
  return _name;
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

  BLEDevice::init(_name.c_str());
  _bleServer = BLEDevice::createServer();
  _bleServer->setCallbacks(new LRMServerCallbacks(this));

  _midiService = new MIDIService(this);
  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  Serial.printf("BLE Advertising is now started as [%s].\n", _name.c_str());
}

BLEService *LRMServer::createBLEService(String uuid) {
  return _bleServer->createService(BLEUUID(uuid.c_str()));
}
