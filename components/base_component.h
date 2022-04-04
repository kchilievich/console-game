#pragma once

#include <memory>

class BaseComponent {
 public:
  void Turn();

  virtual void SetOwner(std::shared_ptr<Entity> NewOwner);

 protected:
  virtual void TurnInternal() = 0;

  std::weak_ptr<Entity> Owner;
};
