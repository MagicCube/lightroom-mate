#include "MIDIServer.h"

class MIDIServerCallbacks : public BLEServerCallbacks {
public:
  MIDIServerCallbacks(MIDIServer *midiServer) {
    _midiServer = midiServer;
  }

  void onConnect(BLEServer *server) {
    _midiServer->setConnected(true);
  }

  void onDisconnect(BLEServer *server) {
    _midiServer->setConnected(false);
  }

private:
  MIDIServer *_midiServer;
};


MIDIServer::MIDIServer() {
  auto chipId = ESP.getEfuseMac();
  // Only use the last 4 byte as ID
  _name = String("LightroomMate-" + String((uint32_t)chipId));
}

String MIDIServer::getName() {
  return _name;
}

bool MIDIServer::isConnected() {
  return _connected;
}
void MIDIServer::setConnected(bool connected) {
  if (_connected != connected) {
    _connected = connected;
    if (_connected) {
      Serial.println("BLE client is now connected.");
    } else {
      Serial.println("BLE client is now disconnected.");
    }
  }
}

void MIDIServer::begin() {
  Serial.println("Initializing MIDI Server...");

  BLEDevice::init(_name.c_str());
  _bleServer = BLEDevice::createServer();
  _bleServer->setCallbacks(new MIDIServerCallbacks(this));

  _midiService = new MIDIService(_bleServer);
  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  Serial.printf("BLE Advertising is now started as [%s].\n", _name.c_str());
}
