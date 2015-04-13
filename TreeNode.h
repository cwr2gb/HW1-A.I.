// Charles Regan
// cwr2gb
// TreeNode.h: TreeNode class definition


#ifndef TREENODE_H
#define TREENODE_H

#include <string>
using namespace std;

class TreeNode {
public:
    TreeNode();						//Default Constructor
    TreeNode(string & val);	//Constructor
    string value;
    TreeNode *left, *right;			// for trees

private:

};

#endif
