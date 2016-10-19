#include "midi.h"
#include "keyboard.h"
#include <Arduino.h>

#define CHANNEL_BIT_1 A3
#define CHANNEL_BIT_2 A2
#define CHANNEL_BIT_3 A1
#define CHANNEL_BIT_4 A0

#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90

#define MIDI_FIRST_KEY 60
#define MIDI_KEYS 29

namespace MIDI {
  uint8_t channel = 0;
  uint8_t command_in = 0;
  int8_t parameter_1_in = -1;

  void setup() {
    Serial1.begin(31250);

    pinMode(CHANNEL_BIT_1, INPUT);
    pinMode(CHANNEL_BIT_2, INPUT);
    pinMode(CHANNEL_BIT_3, INPUT);
    pinMode(CHANNEL_BIT_4, INPUT);
  }

  void read_channel() {
    channel =
        digitalRead(CHANNEL_BIT_1) +
        (digitalRead(CHANNEL_BIT_2) << 1) +
        (digitalRead(CHANNEL_BIT_3) << 2) +
        (digitalRead(CHANNEL_BIT_4) << 3);
  }

  void process_messages() {
    read_channel();

    while (Serial1.available() > 0) {
      uint8_t midi_data = Serial1.read();

      if (midi_data >= MIDI_NOTE_OFF) {
        uint8_t received_channel = midi_data % 0x10;

        if (received_channel == channel) {
          command_in = midi_data - channel;
        }
      } else if (parameter_1_in == -1) {
        switch (command_in) {
          case MIDI_NOTE_OFF:
          case MIDI_NOTE_ON:
            parameter_1_in = midi_data;
            break;
        }
      } else {
        if (parameter_1_in >= MIDI_FIRST_KEY &&
            parameter_1_in < MIDI_FIRST_KEY + MIDI_KEYS) {
          uint8_t key = parameter_1_in - MIDI_FIRST_KEY;

          switch (command_in) {
            case MIDI_NOTE_ON:
              if (midi_data > 0x00) {
                Keyboard::key_on(key);
              } else {
                Keyboard::key_off(key);
              }
              break;
            case MIDI_NOTE_OFF:
              Keyboard::key_off(key);
              break;
          }
        }

        parameter_1_in = -1;
      }
    }
  }
}
