#pragma once

#include <Arduino.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "../constants.h"

#include "../services/MIDIService.h"

class MIDIServer {
public:
  MIDIServer();

  String getName();

  void begin();

private:
  String _name;
  BLEServer *_bleServer;
  MIDIService *_midiService;
};
