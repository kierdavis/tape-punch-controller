#include "Solenoids.hpp"

int main() {
  Solenoids::init();
  Solenoids::activate(0x53);
  Solenoids::deactivate();
}
