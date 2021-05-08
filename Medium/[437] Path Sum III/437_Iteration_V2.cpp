
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

#define NUM_OF_PSEUDO_HEAD  ( 1 )

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        
        
        // the count of satisfied path
        int nPathNum = 0;
        
        // make a pseudo-head "before" root, i.e. pseudo-head
        TreeNode PseudoHead = TreeNode( 0, root, nullptr );
        vector<TreeNode*> Branch( 1, &PseudoHead );
        int nBranchBodyLength = 0;

        while( true ) {
            
            // find a head to tail list, go left only
            while( root ) {
                if( NUM_OF_PSEUDO_HEAD + nBranchBodyLength < Branch.size() ) {
                    nBranchBodyLength++;
                    Branch[ nBranchBodyLength ] = root;
                }
                else {
                    nBranchBodyLength++;
                    Branch.push_back( root );
                }
                root = root->left;
            }

            // calculate the number of the satisfied sub-path which includes "tail"
            // the sub-path here is "left-linked path without divert node"
            while( true ) {
                
                // if the right of current tail exist -> the current tail is not a real tail
                if( Branch[ nBranchBodyLength ]->right != nullptr ) {
                    break;
                }
 
                // calc the sum from the tail to back to root
                int nSumFromTail = 0;
                for( int i = nBranchBodyLength; i >= 1; i-- ) {

                    nSumFromTail += Branch[ i ]->val;
                    nPathNum += ( nSumFromTail == sum );
                }

                // take out the tail
                nBranchBodyLength--;

                // if the branch has been popped out to pseudo-head
                if( nBranchBodyLength <= 0 ) {
                    return nPathNum;
                }
            }

            // update the root with the node linked to left of tail
            root = Branch[ nBranchBodyLength ]->right;

            // move the "right side" divergent path of the tail of branch to "left side"
            Branch[ nBranchBodyLength ]->left = root;
            Branch[ nBranchBodyLength ]->right = nullptr;
        }
        return nPathNum;
    }

};