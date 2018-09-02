#include "MIDIService.h"

#include <BLE2902.h>

#include "../server/LRMServer.h"

#include "MIDICharacteristicCallbacks.h"

MIDIService::MIDIService(LRMServer *server) : Service(server, MIDI_SERVICE_UUID) {
  _bleCharacteristic = this->createCharacteristic(MIDI_CHARACTERISTIC_UUID,
                                                  BLECharacteristic::PROPERTY_READ |
                                                      BLECharacteristic::PROPERTY_NOTIFY |
                                                      BLECharacteristic::PROPERTY_WRITE_NR);
  _bleCharacteristic->addDescriptor(new BLE2902());
  _bleCharacteristic->setCallbacks(new MIDICharacteristicCallbacks(this));
}

void MIDIService::begin() {
  Service::begin();
  Serial.println("MIDI service is now started.");
}

void MIDIService::sendMIDIEvent(MIDIEvent event) {
  uint8_t arr[5];
  event.toArray(arr);
  _bleCharacteristic->setValue(arr, 5);
  _bleCharacteristic->notify();
}

void MIDIService::receiveMIDIEvent(MIDIEvent event) {
  Serial.println("\n*******************************");
  event.print();
  Serial.println("*******************************\n");
}
