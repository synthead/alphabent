#include "midi.h"
#include "keyboard.h"

void setup() {
  MIDI::setup();
  Keyboard::setup();
}

void loop() {
  MIDI::process_messages();
}
