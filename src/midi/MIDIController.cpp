#include "MIDIController.h"

#include "../midi/MIDIEvent.h"

MIDIController::MIDIController(MIDIProvider *midiProvider) {
  _midiProvider = midiProvider;
  _midiProvider->onReceive(
      std::bind(&MIDIController::_handleMIDIServiceReceive, this, placeholders::_1));
}

uint8_t MIDIController::getChannel() {
  return _channel;
}

void MIDIController::setChannel(uint8_t channel) {
  _channel = channel;
}

Key *MIDIController::registerKey(uint8_t pin) {
  Key *key = new Key(_midiNoteIndex++, pin);
  key->onKeyDown(std::bind(&MIDIController::_handleKeyDown, this, placeholders::_1));
  key->onKeyUp(std::bind(&MIDIController::_handleKeyUp, this, placeholders::_1));
  _keys.add(key);
  return key;
}

Encoder *MIDIController::registerEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin) {
  Encoder *encoder = new Encoder(_midiControllerIndex++, clkPin, dtPin);
  encoder->onChange(std::bind(&MIDIController::_handleEncoderChange, this, placeholders::_1));
  _encoders.add(encoder);
  return encoder;
}

void MIDIController::begin() {
  for (auto key : _keys) {
    key->begin();
  }
  for (auto encoder : _encoders) {
    encoder->begin();
  }
}

void MIDIController::update() {
  for (auto key : _keys) {
    key->update();
  }
  for (auto encoder : _encoders) {
    encoder->update();
  }
}

void MIDIController::_handleKeyDown(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::NOTE_ON, getChannel(), e.index, 127);
}

void MIDIController::_handleKeyUp(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::NOTE_OFF, getChannel(), e.index, 0);
}

void MIDIController::_handleEncoderChange(EncoderEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::CONTROL_CHANGE, getChannel(), e.index, e.value);
  Serial.print("[LOCAL]  Set Control #");
  Serial.print(e.index);
  Serial.print(" to [");
  Serial.print(e.value);
  Serial.print("].");
  Serial.println();
}

void MIDIController::_handleMIDIServiceReceive(MIDIEventArgs e) {
  if (e.type == MIDIEventType::CONTROL_ON_CHANGE) {
    if (e.channel == getChannel()) {
      for (auto encoder : _encoders) {
        if (encoder->getIndex() == e.index) {
          encoder->setValue(e.value);
          Serial.print("[REMOTE] Set Control #");
          Serial.print(encoder->getIndex());
          Serial.print(" to [");
          Serial.print(e.value);
          Serial.print("].");
          Serial.println();
        }
      }
    }
  }
}
