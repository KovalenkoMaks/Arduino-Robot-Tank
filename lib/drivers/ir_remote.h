#pragma once

#include <Arduino.h>

// NEC remote receiver on pin A0.
class IrRemote {
public:
  void begin() const;

  // True when a key was pressed since the last call. Repeats from a held key are dropped.
  bool poll(uint8_t& key) const;
};
