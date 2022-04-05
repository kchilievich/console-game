#pragma once

#include "entity.cpp"

class Action;

class Enemy : public Entity {
 public:
  Enemy();

  virtual void Act() override;

  void SetTarget(Entity* NewPlayer);

  virtual std::string GetName() const override { return "Enemy"; }

 protected:
  virtual void SetupIcon() override;
  virtual void Reset() override;

  Action* AttackAction;

 private:
  Entity* Target = nullptr;
};
