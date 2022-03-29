#pragma once

class Action {
 public:
  string GetName() const { return Name; };

  virtual void Perform() {};
 protected:
  string Name = "Nothing";
};
