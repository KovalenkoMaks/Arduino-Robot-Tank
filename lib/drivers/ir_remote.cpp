#include "ir_remote.h"

// TinyIRReceiver is used instead of the full IRremote receiver because it works from a
// pin change interrupt. The full receiver needs Timer2, which drives the motor PWM pins.
//
// The pin is picked by the preprocessor, so it has to be a macro and has to be spelled "A0".
#define IR_RECEIVE_PIN A0
// The default feedback LED is pin 13, which is a motor direction pin on this robot.
#define NO_LED_FEEDBACK_CODE
#include <TinyIRReceiver.hpp>

void IrRemote::begin() const {
  initPCIInterruptForTinyIRReceiver();
}

bool IrRemote::poll(uint8_t& key) const {
  if (!TinyIRReceiverDecode()) {
    return false;
  }
  if (TinyIRReceiverData.Flags & (IRDATA_FLAGS_IS_REPEAT | IRDATA_FLAGS_PARITY_FAILED)) {
    return false;
  }
  key = TinyIRReceiverData.Command;
  return true;
}
