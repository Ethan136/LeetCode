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
        
        // find result
        while( true ) {
            
            // calculate the remained sum "from the current root"
            targetSum -= root->val;
            
            // specify whether it necessary to record the divert point
            switch( GET_NODE_TYPE( root ) ) {
            
                case NodeType_Leaf:
                    
                    // check if reduced target sum is zero
                    return ( targetSum == 0 );
                    
                case NodeType_LinkLeft:
                    
                    // go to next node
                    root = root->left;
                    break;
                    
                case NodeType_LinkRight:
                    
                    // go to next node
                    root = root->right;
                    break;
                    
                case NodeType_Divert:
                    
                    // check left part, if false, then check right
                    return ( hasPathSum( root->left, targetSum ) || hasPathSum( root->right, targetSum ) );
            }
        
        }
        
        // exceptional case
        return false;
    }
};