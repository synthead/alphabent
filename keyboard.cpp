#include "keyboard.h"
#include <Arduino.h>

#define KEYBOARD_COLUMNS 4
#define KEYBOARD_ROWS 8

namespace Keyboard {
  uint8_t column_pins[KEYBOARD_COLUMNS] = {15, 16, 14, 10};
  uint8_t row_pins[KEYBOARD_ROWS] = {4, 5, 3, 6, 2, 7, 8, 9};

  int active_column_pin = -1;
  int active_row_pin = -1;

  void setup() {
    uint8_t pin_i;

    for (pin_i = 0; pin_i < KEYBOARD_COLUMNS; pin_i++) {
      pinMode(column_pins[pin_i], OUTPUT);
    }

    for (pin_i = 0; pin_i < KEYBOARD_ROWS; pin_i++) {
      pinMode(row_pins[pin_i], OUTPUT);
    }
  }

  void key_on(uint8_t key) {
    int column_pin = column_pins[key / KEYBOARD_ROWS];
    int row_pin = row_pins[key % KEYBOARD_ROWS];

    if (active_column_pin != column_pin ||
        active_row_pin != row_pin) {
      digitalWrite(active_column_pin, LOW);
      digitalWrite(active_row_pin, LOW);

      digitalWrite(column_pin, HIGH);
      digitalWrite(row_pin, HIGH);

      active_column_pin = column_pin;
      active_row_pin = row_pin;
    }
  }

  void key_off(uint8_t key) {
    int column_pin = column_pins[key / KEYBOARD_ROWS];
    int row_pin = row_pins[key % KEYBOARD_ROWS];

    if (active_column_pin == column_pin ||
        active_row_pin == row_pin) {
      digitalWrite(active_column_pin, LOW);
      digitalWrite(active_row_pin, LOW);

      active_column_pin = -1;
      active_row_pin = -1;
    }
  }
}
