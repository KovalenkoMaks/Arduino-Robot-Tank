#include "greeting.h"

#include "icons.h"

namespace {

struct Frame {
  const uint8_t* image;  // nullptr is a blank screen
  uint16_t durationMs;
};

const Frame FRAMES[] = {
    {nullptr, 500},        {icons::TEXT_MA, 800}, {nullptr, 400},
    {icons::TEXT_MA, 800}, {nullptr, 400},        {icons::TEXT_HI, 1500},
};
constexpr uint8_t FRAME_COUNT = sizeof(FRAMES) / sizeof(FRAMES[0]);

}  // namespace

void Greeting::start() {
  running_ = true;
  frame_ = 0;
  frameStartedAt_ = millis();
  showFrame();
}

void Greeting::cancel() {
  running_ = false;
}

bool Greeting::running() const {
  return running_;
}

bool Greeting::update() {
  if (!running_) {
    return false;
  }

  const unsigned long now = millis();
  if (now - frameStartedAt_ < FRAMES[frame_].durationMs) {
    return false;
  }

  frame_++;
  if (frame_ == FRAME_COUNT) {
    running_ = false;
    return true;
  }
  frameStartedAt_ = now;
  showFrame();
  return false;
}

void Greeting::showFrame() const {
  const uint8_t* image = FRAMES[frame_].image;
  if (image == nullptr) {
    matrix_.clear();
  } else {
    matrix_.show(image);
  }
}
