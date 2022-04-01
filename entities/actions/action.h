#pragma once

class Action {
 public:
  string GetName() const { return Name; };

  virtual void Perform(Entity* Source, Entity* Target) {};

 protected:
  string Name = "Nothing";
};
