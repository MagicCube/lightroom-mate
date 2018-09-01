#pragma once

#include <Arduino.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "../constants.h"

#include "../services/MIDIService.h"

// Represents the Lightroom Mate server.
class LRMServer {
public:
  LRMServer();

  String getName();
  MIDIService *getMIDIService();

  bool isConnected();
  void setConnected(bool connected);

  void begin();
  BLEService *createBLEService(String uuid);

private:
  String _name;
  bool _connected = false;
  BLEServer *_bleServer;
  MIDIService *_midiService;
};
