#include "led_matrix.h"

namespace {

constexpr uint8_t CMD_FIRST_COLUMN = 0xC0;
constexpr uint8_t CMD_DISPLAY_ON = 0x8A;
constexpr unsigned int BIT_DELAY_US = 3;

}  // namespace

void LedMatrix::begin() const {
  pinMode(pins_.scl, OUTPUT);
  pinMode(pins_.sda, OUTPUT);
  clear();
}

void LedMatrix::show(const uint8_t* image) const {
  uint8_t columns[COLUMNS];
  memcpy_P(columns, image, COLUMNS);
  write(columns);
}

void LedMatrix::clear() const {
  const uint8_t empty[COLUMNS] = {};
  write(empty);
}

void LedMatrix::write(const uint8_t* columns) const {
  start();
  send(CMD_FIRST_COLUMN);
  for (uint8_t i = 0; i < COLUMNS; i++) {
    send(columns[i]);
  }
  end();

  start();
  send(CMD_DISPLAY_ON);
  end();
}

void LedMatrix::start() const {
  digitalWrite(pins_.scl, HIGH);
  delayMicroseconds(BIT_DELAY_US);
  digitalWrite(pins_.sda, HIGH);
  delayMicroseconds(BIT_DELAY_US);
  digitalWrite(pins_.sda, LOW);
  delayMicroseconds(BIT_DELAY_US);
}

// Bits go out least significant first, latched on the rising clock edge.
void LedMatrix::send(uint8_t data) const {
  for (uint8_t bit = 0; bit < 8; bit++) {
    digitalWrite(pins_.scl, LOW);
    delayMicroseconds(BIT_DELAY_US);
    digitalWrite(pins_.sda, (data & 0x01) ? HIGH : LOW);
    delayMicroseconds(BIT_DELAY_US);
    digitalWrite(pins_.scl, HIGH);
    delayMicroseconds(BIT_DELAY_US);
    data >>= 1;
  }
}

void LedMatrix::end() const {
  digitalWrite(pins_.scl, LOW);
  delayMicroseconds(BIT_DELAY_US);
  digitalWrite(pins_.sda, LOW);
  delayMicroseconds(BIT_DELAY_US);
  digitalWrite(pins_.scl, HIGH);
  delayMicroseconds(BIT_DELAY_US);
  digitalWrite(pins_.sda, HIGH);
  delayMicroseconds(BIT_DELAY_US);
}
