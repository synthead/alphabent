#ifndef MIDI_H
#define MIDI_H

#include <stdint.h>

namespace MIDI {
  void setup();
  void process_messages();
  void read_channel();
}

#endif
