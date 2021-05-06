/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#define FIND_MAX( val1, val2 ) ( ( val1 > val2 ) ? ( val1 ) : ( val2 ) )

class Solution {

    int m_nMaxPathSizeWithSameValue = 0;
    
    int FindMaxDepthWithTargetVal( int nTargetValue, TreeNode *root, vector<TreeNode*> &DivertNodeRecord ) {
        
        if( root == nullptr ) {
            return 0;
        }
        
        if( root->val != nTargetValue ) {
            DivertNodeRecord.push_back( root );
            return 0;
        }
        
        int nLeftDepth = FindMaxDepthWithTargetVal( nTargetValue, root->left, DivertNodeRecord );
        int nRightDepth = FindMaxDepthWithTargetVal( nTargetValue, root->right, DivertNodeRecord );
        
        m_nMaxPathSizeWithSameValue = FIND_MAX( m_nMaxPathSizeWithSameValue, nLeftDepth + nRightDepth );
        return FIND_MAX( nLeftDepth, nRightDepth ) + 1;
    }
    
public:
    int longestUnivaluePath(TreeNode* root) {
        
        if( root == nullptr ) {
            return 0;
        }
        
        vector<TreeNode*> DivertNodeRecord;
        DivertNodeRecord.push_back( root );

        while( DivertNodeRecord.size() ) {
            
            root = DivertNodeRecord.back();
            DivertNodeRecord.pop_back();
            FindMaxDepthWithTargetVal( root->val, root, DivertNodeRecord );
        }
            
        return  m_nMaxPathSizeWithSameValue;
    }
};