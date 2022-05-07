#pragma once

#include "../entity.cpp"

class Wall : public Entity {
 public:
  Wall();

 protected:
  virtual void SetupIcon() override;
};
