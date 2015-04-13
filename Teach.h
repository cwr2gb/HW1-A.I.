#ifndef TEACH_H
#define TEACH_H

#include <iostream>

using namespace std;

class Teach {
public:
  Teach(string var, string str, bool tof);               
  Teach(string exp, string varf);
  void setTrue();
  void setFalse();
  bool getTruth() const;
  string getVar() const;
  string getStr() const;
  string getExp() const;
  string getVarf() const;

 private:

  string var;
  string str;
  bool tof;
  string exp;
  string varf;
  
};

#endif
