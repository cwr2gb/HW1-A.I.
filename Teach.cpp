//Teach.cpp
#include "Teach.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Teach::Teach(string var1, string str1, bool tof1){
  var = var1;
  str = str1;
  tof = tof1;
}
Teach::Teach(string exp1, string varf1){
  exp = exp1;
  varf = varf1;
}
void Teach::setTrue(){
  tof = true;
}
void Teach::setFalse(){
  tof = false;
}
bool Teach::getTruth() const{
  return tof;
}
string Teach::getVar() const{
  return var;
}
string Teach::getStr() const{
  return str;
}
string Teach::getExp() const{
  return exp;
}
string Teach::getVarf() const{
  return varf;
}