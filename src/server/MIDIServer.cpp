#include "MIDIServer.h"

MIDIServer::MIDIServer() {
  auto chipid = ESP.getEfuseMac();
  // Only use the last 4 byte as ID
  _name = String("LightroomMate-" + String((uint32_t)chipid));
}

String MIDIServer::getName() {
  return _name;
}

void MIDIServer::begin() {
  Serial.println("Initializing MIDI Server...");

  BLEDevice::init(_name.c_str());
  _bleServer = BLEDevice::createServer();

  _midiService = new MIDIService(_bleServer);
  _midiService->begin();

  _bleServer->getAdvertising()->addServiceUUID(MIDI_SERVICE_UUID);
  _bleServer->getAdvertising()->start();

  Serial.printf("BLE Advertising is now started as [%s].\n", _name.c_str());
}
