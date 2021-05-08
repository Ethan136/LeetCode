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
        
        // check if root exist
        if( root == nullptr ) {
            return false;
        }
    
        // temporary variable for data swap
        TreeNode *pLeftNode;
        
        // use a stack to store the first node, e.g. root
        TreeNode *pStackHead = nullptr;
        
        // find result
        while( true ) {
            
            // calculate the remained sum "from the current root"
            targetSum -= root->val;
            
            // specify whether it necessary to record the divert point
            switch( GET_NODE_TYPE( root ) ) {
            
                case NodeType_Leaf:
                    
                    // if reduced target sum is zero
                    if( targetSum == 0 ) {
                        return true;
                    }
                    
                    // if total branch sum is different from target value
                    // AND "the head of stack does not exist" -> can't go back
                    if( pStackHead == nullptr ) {
                        return false;
                    }
                    
                    // go back to the position of stack head
                    targetSum = pStackHead->val;
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
                    
                    // record the current target sum
                    pStackHead->val = targetSum;
                    break;
            }
        
        }
        
        // exceptional case
        return false;
    }
};