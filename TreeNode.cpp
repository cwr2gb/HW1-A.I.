// Charles Regan
// cwr2gb
// TreeNode.cpp:  Tree Node method implementations

#include "TreeNode.h"

//Default Constructor -left and right are NULL, value '?'
TreeNode::TreeNode() {
    value="?";
    left=NULL;
    right=NULL;
}

//Constructor - sets value to val
TreeNode::TreeNode(string & val) {
    value=val;
    left=NULL;
    right=NULL;
}
