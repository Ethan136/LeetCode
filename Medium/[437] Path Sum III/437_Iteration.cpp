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
struct TNodeInfo {
    TreeNode* pNode;
    int nSumFromRoot;
    TNodeInfo( TreeNode *pNode, int nSumFromRoot ) : nSumFromRoot( nSumFromRoot ), pNode( pNode ) {}
};

#define NUM_OF_PSEUDO_HEAD  ( 1 )

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        
        
        // the count of satisfied path
        int nPathNum = 0;
        
        // make a head "before" root, i.e. pseudo-head
        TreeNode PseudoHeadNode( 0, root, nullptr );
        vector<TNodeInfo> Branch( 1, TNodeInfo( &PseudoHeadNode, PseudoHeadNode.val ) );
        int nBranchBodyLength = 0;

        while( true ) {
            
            // find a head to tail list, go left only
            while( root ) {
                if( NUM_OF_PSEUDO_HEAD + nBranchBodyLength >= Branch.size() ) {
                    Branch.push_back( TNodeInfo( nullptr, 0 ) );
                }
                nBranchBodyLength++;
                Branch[ nBranchBodyLength ].pNode = root;
                Branch[ nBranchBodyLength ].nSumFromRoot = Branch[ nBranchBodyLength - 1 ].nSumFromRoot + root->val;
                root = root->left;
            }

            // calculate the number of the satisfied sub-path which includes "tail"
            // the sub-path here is "left-linked single path"
            while( nBranchBodyLength > 0 ) {
                
                // if the right of current tail exist -> the current tail is not a real tail
                if( Branch[ nBranchBodyLength ].pNode->right != nullptr ) {
                    break;
                }

				// sum to the current tail
				int nSumToTail = Branch[ nBranchBodyLength ].nSumFromRoot;
 
                // take out the nodes from pseudo-head to "node before the tail"
                for( int i = 0; i < nBranchBodyLength; i++ ) {
                    nSumToTail -= Branch[ i ].pNode->val;
                    nPathNum += ( nSumToTail == sum );
                }

                // take out the tail
                nBranchBodyLength--;
            }

            // if the branch has been totally popped out
            if( nBranchBodyLength <= 0 ) {
                break;
            }
            
            // move the "right side" divergent path of the tail of branch to "left side"
            Branch[ nBranchBodyLength ].pNode->left = Branch[ nBranchBodyLength ].pNode->right;
            Branch[ nBranchBodyLength ].pNode->right = nullptr;
            
            // update the root with the node linked to left of tail
            root = Branch[ nBranchBodyLength ].pNode->left;
        }
        return nPathNum;
    }

};