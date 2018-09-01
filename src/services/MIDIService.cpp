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

void MIDIService::sendMIDIEvent(uint8_t type, uint8_t id, uint8_t value) {
  uint8_t midiPacket[] = {
      0x80, // 0 - header
      0x80, // 1 - timestamp, not implemented
      0x00, // 2 - type
      0x00, // 3 - m1
      0x00  // 4 - m2
  };
  midiPacket[2] = type;
  midiPacket[3] = id;
  midiPacket[4] = value;
  _bleCharacteristic->setValue(midiPacket, 5);
  _bleCharacteristic->notify();
}
