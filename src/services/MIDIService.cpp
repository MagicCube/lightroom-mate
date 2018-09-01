#include "MIDIService.h"

#include <BLE2902.h>

#include "../server/LRMServer.h"

MIDIService::MIDIService(LRMServer *server) : Service(server, MIDI_SERVICE_UUID) {
  _bleCharacteristic = this->createCharacteristic(MIDI_CHARACTERISTIC_UUID,
                                                  BLECharacteristic::PROPERTY_READ |
                                                      BLECharacteristic::PROPERTY_NOTIFY |
                                                      BLECharacteristic::PROPERTY_WRITE_NR);
  _bleCharacteristic->addDescriptor(new BLE2902());
}

void MIDIService::begin() {
  Service::begin();
  Serial.println("MIDI service is now started.");
}
