#include "FeedbackSignal.hpp"
#include "Solenoids.hpp"
#include "TapePunch.hpp"
#include "TapePunchTimer.hpp"

void TapePunch::init() {
  FeedbackSignal::init();
  Solenoids::init();
  TapePunchTimer::init();
}

void TapePunch::sync() {
  TapePunchTimer::start();
}

void TapePunch::energiseSolenoids() {
  Solenoids::energise(0xFF);
}

void TapePunch::deenergiseSolenoids() {
  Solenoids::deenergise();
}

void TapePunch::flagSyncTimeout() {
  // TODO
}
