
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

enum ELinkType {
	LinkType_NULL,
	LinkType_Leaf,
	LinkType_LeftLink,
	LinkType_RightLink,
	LinkType_Root,
};

#define IS_SAME_VALUE_LINK_LEFT( Node ) ( ( Node->left != nullptr ) && ( Node->left->val == Node->val ) )
#define IS_SAME_VALUE_LINK_RIGHT( Node ) ( ( Node->right != nullptr ) && ( Node->right->val == Node->val ) )

#define CHECK_SAME_VALUE_LINK_TYPE( Node ) \
( IS_SAME_VALUE_LINK_LEFT( Node ) ? ( IS_SAME_VALUE_LINK_RIGHT( Node ) ? LinkType_Root : LinkType_LeftLink ) : ( IS_SAME_VALUE_LINK_RIGHT( Node ) ? LinkType_RightLink : LinkType_Leaf ) )

#define FIND_MAX( val1, val2 ) ( ( val1 > val2 ) ? ( val1 ) : ( val2 ) )

class Solution {

    int ExploreToEndNode( TreeNode* root, int nDepthFromTop, int &nMaxSameValTreeDiameter ) {

		while( root ) {

			switch( CHECK_SAME_VALUE_LINK_TYPE( root ) ) {

			case LinkType_Leaf:
				ExploreToEndNode( root->left, 0, nMaxSameValTreeDiameter );
				ExploreToEndNode( root->right, 0, nMaxSameValTreeDiameter );
				nMaxSameValTreeDiameter = FIND_MAX( nMaxSameValTreeDiameter, nDepthFromTop );
				return nDepthFromTop;

			case LinkType_LeftLink:
				ExploreToEndNode( root->right, 0, nMaxSameValTreeDiameter );
				nDepthFromTop++;
				root = root->left;
				break;

			case LinkType_RightLink:
				ExploreToEndNode( root->left, 0, nMaxSameValTreeDiameter );
				nDepthFromTop++;
				root = root->right;
				break;

			case LinkType_Root: {
				int nLeftDivertDepth = ExploreToEndNode( root->left, 1, nMaxSameValTreeDiameter );
				int nRightDivertDepth = ExploreToEndNode( root->right, 1, nMaxSameValTreeDiameter );
				nMaxSameValTreeDiameter = FIND_MAX( nMaxSameValTreeDiameter, ( nLeftDivertDepth + nRightDivertDepth ) );
				return nDepthFromTop + FIND_MAX( nLeftDivertDepth, nRightDivertDepth );
			}
			default:
				return nDepthFromTop;
			}
		}
		return nDepthFromTop;
	}

public:
	int longestUnivaluePath( TreeNode *root ) {

		int nMaxSamValTreeDiameter = 0;
		ExploreToEndNode( root, 0, nMaxSamValTreeDiameter );

		return nMaxSamValTreeDiameter;
	}
};