#ifndef _BODY_H_
#define _BODY_H_

class Body
{
public:
  Body(int pin, int *sequence);
  void run();

private:
  int _pin;
  int *_sequence;
};

#endif