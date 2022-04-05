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

void Attributes::SetHealthBase(float NewHealthBase) {
  float Delta = (NewHealthBase - MaxHealthBase) / MaxHealthBase;
  MaxHealthBase = NewHealthBase;
  RecalculateCurrentHealth(Delta);
}

void Attributes::SetHealthModifier(float NewHealthModifier) {
  float Delta = NewHealthModifier - MaxHealthModifier;
  MaxHealthModifier = NewHealthModifier;
  RecalculateCurrentHealth(Delta);
}

void Attributes::RecalculateCurrentHealth(float Delta) {
  Health = Health * Delta; // TODO: Might think of that again
}

void Attributes::TurnInternal() { }
