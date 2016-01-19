#pragma once

template <class A> class inputProcess {
public:
  A val;
  virtual void setup() = 0;
  virtual void update() = 0;
  virtual void draw() {};
  virtual ~inputProcess() {};
};
