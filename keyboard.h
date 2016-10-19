#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

namespace Keyboard {
  void setup();
  void key_on(uint8_t);
  void key_off(uint8_t);
}

#endif
