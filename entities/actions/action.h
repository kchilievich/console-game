#pragma once

class Action {
 public:
  virtual string GetName() const { return "Nothing"; };

  virtual void Perform(Entity* Source, Entity* Target) {};
};
