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
private:
    void FindpathSum(TreeNode* root, int targetSum, vector<int> &path, vector<vector<int>> &PathContainer ) {
        
        // if root does not exist
        if( root == nullptr ) {
            return;
        }
        
        // the origin size of path
        int nPathOriginSize = path.size();
        
        // find result
        while( true ) {
            
            // calculate the remained sum "from the current root"
            targetSum -= root->val;
            
            // store value of current node
            path.push_back( root->val );
            
            // specify whether it necessary to record the divert point
            switch( GET_NODE_TYPE( root ) ) {
            
                case NodeType_Leaf:
                    
                    // restore the path
                    if( targetSum == 0 ) {
                        PathContainer.push_back( path );
                    }
                    
                    // retore the path back to the initial condition
                    path.resize( nPathOriginSize );
                    return;
                    
                case NodeType_LinkLeft:
                    root = root->left;
                    break;
                    
                case NodeType_LinkRight:
                    root = root->right;
                    break;
                    
                case NodeType_Divert:
                    
                    // find path in both direction
                    FindpathSum( root->left, targetSum, path, PathContainer );
                    FindpathSum( root->right, targetSum, path, PathContainer );
                    
                    // retore the path back to the initial condition
                    path.resize( nPathOriginSize );
                    return;
            }
        
        }
    };

public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
                
        // for the current branch-path in validation
        vector<int> path;

        // the resultant data
        vector<vector<int>> Result;
        
        // find all results
        FindpathSum( root, targetSum, path, Result );
        
        // return result
        return Result;
    }
};