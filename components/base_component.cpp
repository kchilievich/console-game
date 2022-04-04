#include "base_component.h"

void BaseComponent::Turn() {
  TurnInternal();
}

void BaseComponent::SetOwner(std::shared_ptr<Entity> NewOwner) {
  Owner = NewOwner;
}
