#pragma once

#include "base_component.h"

class Attributes : public BaseComponent {
public:
  float GetHealth() const;
  float GetMaxHealth() const;

  void ModifyHealth(float Delta);

  void SetHealthBase(float NewHealthBase);
  void SetHealthModifier(float NewHealthModifier);

protected:
  virtual void TurnInternal() override;

private:
  void RecalculateCurrentHealth(float Delta);

  float Health = 100.f;
  float MaxHealthBase = 100.f;
  float MaxHealthModifier = 1.f;
};
