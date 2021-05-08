enum ENodeType {
    NodeType_Leaf = 0,
    NodeType_LinkLeft = 1,
    NodeType_LinkRight = 2,
    NodeType_Divert = 3,
};

// get node type
#define GET_NODE_TYPE( Node )                                                   \
( Node->left != nullptr ) ?                                                     \
( ( Node->right != nullptr ) ? ( NodeType_Divert ) : ( NodeType_LinkLeft ) ) :  \
( ( Node->right != nullptr ) ? ( NodeType_LinkRight ) : ( NodeType_Leaf ))


class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
    
        // temporary variable for data swap
        TreeNode *pLeftNode;
        
        // use a stack to store the diverting node
        TreeNode *pStackHead = nullptr;
        
        // sum of current branch
        int nBranchSum = 0;
        
        // find result
        while( root != nullptr ) {
            
            // do add
            nBranchSum += root->val;
            
            // specify whether it necessary to record the divert point
            switch( GET_NODE_TYPE( root ) ) {
            
                case NodeType_Leaf:
                    
                    // if total branch sum is equal to target value
                    if( nBranchSum == targetSum ) {
                        return true;
                    }
                    
                    // if total branch sum is different from target value
                    // AND "the head of stack does not exist" -> can't go back
                    if( pStackHead == nullptr ) {
                        return false;
                    }
                    
                    // go back to the position of stack head
                    nBranchSum = pStackHead->val;
                    root = pStackHead->right;
                    pStackHead = pStackHead->left;
                    break;
                    
                case NodeType_LinkLeft:
                    
                    // go to next node
                    root = root->left;
                    break;
                    
                case NodeType_LinkRight:
                    
                    // go to next node
                    root = root->right;
                    break;
                    
                case NodeType_Divert:
                    
                    // backup origin left node
                    pLeftNode = root->left;
                    
                    // record to stack
                    root->left = pStackHead;
                    pStackHead = root;
                    
                    // advance root to left node
                    root = pLeftNode;
                    
                    // record the current branch sum
                    pStackHead->val = nBranchSum;
                    break;
            }
        
        }
        
        // in the above cases, the root node supposed to be exist
        return false;
    }
};