#pragma once

#include "../entity.cpp"

class Wall : public Entity {
 public:
  Wall();

  void SetPosition(int x, int y);

 protected:
  virtual void SetupIcon() override;
};
