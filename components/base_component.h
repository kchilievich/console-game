#pragma once

class BaseComponent {
 public:
  void Turn();

 protected:
  virtual void TurnInternal() = 0;
};
