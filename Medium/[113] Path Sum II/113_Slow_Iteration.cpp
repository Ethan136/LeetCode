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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        
        // resultant data
        vector<vector<int>> Result;
        
        // if input does not exist
        if( root == nullptr ) {
            return Result;
        }
        
        // the current branch in check
        vector<int> CurrentBranch;
        
        // use a stack to store the first node, e.g. root
        // and a temporary variable for data swap
        TreeNode *pStackHead = nullptr;
        TreeNode *pLeftNode;
        vector<int> DepthToStackHead;

        // find result
        while( true ) {
 
            // record the node of current branch
            CurrentBranch.push_back( root->val );    
            
            // calculate the remained sum "from the current root"
            targetSum -= root->val;
            
            // specify whether it necessary to record the divert point
            switch( GET_NODE_TYPE( root ) ) {
            
                case NodeType_Leaf:
                    
                    // if reduced target sum is zero -> requirement achieved
                    // store the current branch to the result vector
                    if( targetSum == 0 ) {
                        Result.push_back( CurrentBranch );
                    }
                    
                    // if the head of stack does not exist -> can't go back -> FINISH
                    if( pStackHead == nullptr ) {
                        return Result;
                    }
                    
                    // go back to the position of stack head
                    targetSum = pStackHead->val;
                    root = pStackHead->right;
                    
                    // trim the branch to the node depth corresponding to stack head
                    CurrentBranch.resize( DepthToStackHead.back() );
                    
                    // pop out the stack head
                    pStackHead = pStackHead->left;
                    DepthToStackHead.pop_back();
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
                    
                    // convert tree node to stack
                    root->left = pStackHead;
                    pStackHead = root;
                    
                    // record the divert position within the branch
                    DepthToStackHead.push_back( CurrentBranch.size() );
                    
                    // advance root to left node
                    root = pLeftNode;
                    
                    // record the current target sum
                    pStackHead->val = targetSum;
                    break;
            }
        
        }
        
        // exceptional case
        return Result;
    }
};