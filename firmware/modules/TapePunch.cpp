#include "FeedbackSignal.hpp"
#include "Solenoids.hpp"
#include "TapePunch.hpp"
#include "TapePunchTimer.hpp"

void TapePunch::init() {
  FeedbackSignal::init();
  Solenoids::init();
  TapePunchTimer::init();
}

void TapePunch::Callbacks::sync() {
  TapePunchTimer::start();
}

void TapePunch::Callbacks::energiseSolenoids() {
  Solenoids::energise(0xFF);
}

void TapePunch::Callbacks::deenergiseSolenoids() {
  Solenoids::deenergise();
}

void TapePunch::Callbacks::flagSyncTimeout() {
  // TODO
}
