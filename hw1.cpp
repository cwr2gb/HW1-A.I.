//Charles Regan
//cwr2gb
//hw1.cpp
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Teach.h"
#include "TreeNode.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

//prototypes
void tokeN(string s);
bool isString(string s);
bool QueryIt(string s);
void doParen(string s);
void doParen2(string s);
TreeNode* evalExp(vector<string> express, string check);
bool evaluateTruth(TreeNode* tree);
void WhyIt(string s);
string evaluateWhy(TreeNode* tree);
//variables
string doDis, command, exp, sign1, sign2, var1, var2, rSide, rSign, test1, test2, test3, reDostr;
bool truthy1, truthy2;
int p1, p2, p3, cParen;
int countit = 0;
int origin = 0;
int end = 1;
int OP = 0;
int whyC = 0;
vector<Teach>* teachVar = new vector<Teach>;
vector<Teach>* teachExp = new vector<Teach>;
vector<string> tokens;
vector<string> tokens2;
vector<string> evaluate;
string temp;

int main(){
  while(doDis != "quit"){

    getline(cin, doDis);
    
    command = doDis.substr(0,doDis.find(" "));
    p1 = doDis.find(" ")+1;
    
   //Teach Command - DONE///////////////////////////
    if(command == "Teach"){
      
      rSide = doDis.substr(p1, doDis.length());    
      p2 = rSide.find(" ")+1;   
      exp = rSide.substr(0, p2-1);
      sign1 = rSide.substr(p2, rSide.length());
      sign2 = sign1.substr(0,sign1.find(" "));

      if(sign2.compare("=") == 0){
	var1 = sign1.substr(sign1.find(" ")+1,sign1.length());

	if(var1.find("\"")){
	
	  if(var1 == "true"){	  
	    for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){	    
	      if(x->getVar() == exp){
		x->setTrue();
	      }
	    }
	  } 
	  if(var1 == "false"){
	    for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
	      if(x->getVar() == exp){
		x->setFalse();
	      }
	    }
	  }
	}
	else
	  {
	    var1 = sign1.substr(sign1.find(" ")+2,sign1.length());
	    var2 = var1.substr(0, var1.find("\""));
	    Teach add = Teach(exp,var2,false);
	    teachVar->push_back(add);    
	  }
      }
      else if(sign2.compare("->") == 0){
	var1 = sign1.substr(sign1.find(" ")+1,sign1.length());	
	Teach add2 = Teach (exp, var1);
	teachExp->push_back(add2);
      }
    }

    //List Command - DONE///////////////////////////
      if(command == "List"){
	cout << "Variables:" << endl;
	for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
	  cout << "\t" << x->getVar() << " = " << "\"" << x->getStr() <<"\"" << endl;
	}
	cout << "Facts:" << endl;
	for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
	  if(x->getTruth()){
	    cout << "\t" << x->getVar() << endl;
	  }
	}
	cout << "Rules:" << endl;
	for(vector<Teach>::iterator x = teachExp->begin(); x != teachExp->end(); ++x){
	  cout << "\t" << x->getExp() << " -> " << x->getVarf() << endl;
	}
      }

   //Learn Command///////////////////////////
      if(command == "Learn"){
	for(vector<Teach>::iterator x = teachExp->begin(); x != teachExp->end(); ++x){
	  tokens.clear();
	  if(QueryIt(x->getExp())){
	    for(vector<Teach>::iterator y = teachVar->begin(); y != teachVar->end(); ++y){
	      if(x->getVarf() == y->getVar()){
		  y->setTrue();
		}
	      }
	    }
	  }
	 for(vector<Teach>::iterator x = teachExp->begin(); x != teachExp->end(); ++x){
	  tokens.clear();
	  if(QueryIt(x->getExp())){
	    for(vector<Teach>::iterator y = teachVar->begin(); y != teachVar->end(); ++y){
	      if(x->getVarf() == y->getVar()){
		  y->setTrue();
		}
	      }
	    }
	  }
	}
      

   //Query Command///////////////////////////
      if(command == "Query"){
	tokens.clear();
	rSide = doDis.substr(p1, doDis.length());
	  
	  if(QueryIt(rSide)){
	    cout << "true" << endl;
	  }
	  else{
	    cout << "false" << endl; 
	  }
      }

   //Why Command///////////////////////////
      if(command == "Why"){
	tokens.clear();
	rSide = doDis.substr(p1, doDis.length());
	for(vector<Teach>::iterator x = teachExp->begin(); x != teachExp->end(); ++x){
	  tokens.clear();
	  if(QueryIt(x->getExp())){
	    for(vector<Teach>::iterator y = teachVar->begin(); y != teachVar->end(); ++y){
	      if(x->getVarf() == y->getVar()){
		  y->setTrue();
		}
	      }
	    }
	  }
	 for(vector<Teach>::iterator x = teachExp->begin(); x != teachExp->end(); ++x){
	  tokens.clear();
	  if(QueryIt(x->getExp())){
	    for(vector<Teach>::iterator y = teachVar->begin(); y != teachVar->end(); ++y){
	      if(x->getVarf() == y->getVar()){
		  y->setTrue();
		}
	      }
	    }
	  }
	  if(QueryIt(rSide)){
	    cout << "true" << endl;
	    tokens.clear();
	    WhyIt(rSide);
	    whyC = 0;
	  }
	  else{
	    cout << "false" << endl; 
	    tokens.clear();
	    WhyIt(rSide);
	    whyC = 0;
	  }
      }
      
  }
  
}
//Token command that parses expression
void tokeN(string s){  //forall-> && s.length > 1
    if(s.substr(origin, end) == "("){
      cParen++;
      doParen(s);
      test1 = "";
      test2 = "";
      test3 = "";
    }
    else if(s.length() > 1)
    {
      tokens.push_back(s.substr(origin, end));
      string temp1 = s.substr(end, s.length());
      tokeN(temp1);
    }
    else 
    {
      tokens.push_back(s.substr(origin, end));
    }
}

//Token2 command that parses expression
void tokeN2(string s){  //forall-> && s.length > 1
    if(s.substr(origin, end) == "("){
      cParen++;
      doParen2(s);
      test1 = "";
      test2 = "";
      test3 = "";
    }
    else if(s.length() > 1)
    {
      tokens2.push_back(s.substr(origin, end));
      string temp1 = s.substr(end, s.length());
      tokeN2(temp1);
    }
    else 
    {
      tokens2.push_back(s.substr(origin, end));
    }
}
//Determines if S is a string and not a special char
bool isString(string s){
if(s != "!" && s != "&" && s != "|" && s != "(" && s != ")")
  return true;	
else
  return false;
}

//Query command
bool QueryIt(string s){
  if(s.length() == 1){
    for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
      if(s == x->getVar()){
	if(x->getTruth()){
	  return true;
	}
	else
	  return false;
      }
    }  
  }
  else
  {
    tokeN(s);
    return evaluateTruth(evalExp(tokens, ""));
  }
}

//Why command
void WhyIt(string s){
  if(s.length() == 1){
    for(vector<Teach>::iterator a = teachExp->begin(); a != teachExp->end(); ++a){
	  if(a->getVarf() == s){
	    tokeN(a->getExp());
	    cout << "BECAUSE ";
	    tokens.clear();
	    tokeN(a->getExp());
	    evaluateWhy(evalExp(tokens, ""));
	  }
	  for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
	    if(s == x->getVar()){
	      if(x->getTruth()){
		cout << "I KNOW THAT " << x->getStr() << endl;
	      }
	      else
		cout << "I KNOW THAT NOT " << x->getStr() << endl;;
	    
	    }	  
	  }
    }
  }
  else{
    tokens.clear();
    tokeN(s);
    evaluateWhy(evalExp(tokens, ""));
  }
}

//Handles Parenthesis
void doParen(string s){
  
  test1 = test1 + s.substr(0,1);
  test2 = s.substr(1,s.length());
  test3 = test2.substr(0,1);
  if(cParen != 0){
    if(test3 == "("){
      cParen++;
      doParen(test2);
    }

    else if(test3 == ")"){
      cParen--;
      doParen(test2);
    }
    else{
      doParen(test2);
    }
  }
  else{
    tokens.push_back(test1);
    test1 = "";
    tokeN(test2);
  }
}
//Handles Parenthesis
void doParen2(string s){
  
  test1 = test1 + s.substr(0,1);
  test2 = s.substr(1,s.length());
  test3 = test2.substr(0,1);
  if(cParen != 0){
    if(test3 == "("){
      cParen++;
      doParen2(test2);
    }
    else if(test3 == ")"){
      cParen--;
      doParen2(test2);
    }
    else{
      doParen2(test2);
    }
  }
  else{
    tokens2.push_back(test1);
    test1 = "";
    tokeN2(test2);
  }
}
//Gets Tree for Expression
TreeNode* evalExp(vector<string> express, string check){
      TreeNode *eval;
      int count = 0;
      int count2 = 0;

      //OR
      for(vector<string>::reverse_iterator y = express.rbegin(); y != express.rend(); y++){
	count++;
      if(*y == "|"){
	eval = new TreeNode(*y);
	
	//Left
	vector<string> left;
	for(vector<string>::reverse_iterator a = express.rbegin(); a != express.rend(); a++){
	  if(count2 > 0){
	    left.push_back(*a); 
	  }
	  if((*a == *y)){
	    count2++;
	  }
	}	
	eval->left = evalExp(left, *y);
	count2 = 0;
	
	//Right
	vector<string> right;
	for(vector<string>::reverse_iterator d = express.rbegin(); d != express.rend(); d++){
	  if((*d == *y)){
	    count2++;
	  }
	  if(count2 == 0){
	    right.push_back(*d); 
	  }
	}
	eval->right = evalExp(right, *y);
	return eval;
      }
      }
      //AND
      for(vector<string>::reverse_iterator y = express.rbegin(); y != express.rend(); y++){
	count++;
      if(*y == "&"){
	eval = new TreeNode(*y);
	//Left
	vector<string> left;
	for(vector<string>::reverse_iterator a = express.rbegin(); a != express.rend(); a++){
	  if(count2 > 0){
	    left.push_back(*a); 
	  }
	  if((*a == *y)){
	    count2++;
	  }
	}	
	eval->left = evalExp(left, *y);
	count2 = 0;
	
	//Right
	vector<string> right;
	for(vector<string>::reverse_iterator d = express.rbegin(); d != express.rend(); d++){
	  if((*d == *y)){
	    count2++;
	  }
	  if(count2 == 0){
	    right.push_back(*d); 
	  }
	}
	eval->right = evalExp(right, *y);
	return eval;
      }
    }
      //COUNT3    
      int count3 = 0;
      //NOT
      for(vector<string>::reverse_iterator z = express.rbegin(); z != express.rend(); z++){
	count3++;
	if(*z == "!"){
	  eval = new TreeNode(*z);
	  //Right
	  vector<string> right;
	  count2 = 0;
	  if(count3 == 1){
	    for(vector<string>::reverse_iterator v = express.rbegin(); v != express.rend(); v++){
	      if(count2 != 0){
		right.push_back(*v); 
	      }
	      if((*v == *z)){
		count2++;
	      }
	    }
	  }
	  else{
	    for(vector<string>::reverse_iterator v = express.rbegin(); v != express.rend(); v++){
	      if((*v == *z)){
		count2++;
	      }
	      if(count2 == 0){
		right.push_back(*v); 
	      }
	    }
	  }
	  eval->right = evalExp(right, *z);
	  return eval;
	}
      }
      //PAREN
      for(vector<string>::reverse_iterator p = express.rbegin(); p != express.rend(); p++){
	if(p->length() > 1){
	  tokens2.clear();
	  string sub = p->substr(1,p->length()-2);
	  tokeN2(sub);
	  return eval = evalExp(tokens2,"");
	}
      }
      //VAR
      if(check == "|" || check == "&" || check == "!" || express.size() == 1){
      return eval = new TreeNode(express.front());
    }
      return eval;
}

//Evaluates Truth
bool evaluateTruth(TreeNode* tree){
  string operand = tree->value;
  if(operand == "!"){
    return (!evaluateTruth(tree->right));
  }
  else if(operand == "&"){
    return (evaluateTruth(tree->left)&&evaluateTruth(tree->right));
  }
  else if(operand == "|"){
    return (evaluateTruth(tree->left)||evaluateTruth(tree->right));
  }
  else{
    for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
      if(x->getVar() == tree->value){
	return x->getTruth();
      }
    }
  }
    
}

//Evaluates Truth and Prints out logic
string evaluateWhy(TreeNode* tree){
  string operand = tree->value;
  if(operand == "!"){
    whyC++;
    cout << "I KNOW THAT NOT " << evaluateWhy(tree->right) << endl;
    return "";
  }
  else if(operand == "&"){
    whyC++;
    cout << "I KNOW THAT " << evaluateWhy(tree->left) << " AND " << evaluateWhy(tree->right) << endl;
    return "";
  }
  else if(operand == "|"){
    whyC++;
    cout << "I KNOW THAT " << evaluateWhy(tree->left) << " OR " << evaluateWhy(tree->right) << endl;
    return "";
  }
  else{
    for(vector<Teach>::iterator x = teachVar->begin(); x != teachVar->end(); ++x){
      if(x->getVar() == tree->value){
	if(whyC == 0){
	  cout << x-> getStr() << endl;
	}
	return x->getStr();
      }
    }
  }
    
}