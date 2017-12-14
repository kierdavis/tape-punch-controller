#include "FeedbackSignal.hpp"
#include "Hooks.hpp"
#include "Solenoids.hpp"

void Hooks::onFeedbackPulse() {
  Solenoids::activate(0x53);
  Solenoids::deactivate();
}

int main() {
  Solenoids::init();
  FeedbackSignal::init();
}
