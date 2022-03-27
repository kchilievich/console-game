#include "attributes_component.h"

#include <algorithm>

float Attributes::GetHealth() const {
  return Health;
}

float Attributes::GetMaxHealth() const {
  return MaxHealthBase * MaxHealthModifier;
}

void Attributes::ModifyHealth(float Delta) {
  Health = std::clamp(Health + Delta, 0.f, GetMaxHealth());
}

void Attributes::TurnInternal() { }
