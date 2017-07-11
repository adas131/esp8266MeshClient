#ifndef _BODY_H_
#define _BODY_H_

class Body
{
public:
  Body(int pin, long *sequence);
  void run();

private:
  int _pin;
  long *_sequence;
  long _seqPtr;
};

#endif