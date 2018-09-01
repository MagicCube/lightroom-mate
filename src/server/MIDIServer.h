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

  bool isConnected();
  void setConnected(bool connected);

  void begin();

private:
  String _name;
  bool _connected = false;
  BLEServer *_bleServer;
  MIDIService *_midiService;
};
