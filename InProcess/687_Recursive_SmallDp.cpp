#define FIND_MAX( val1, val2 ) ( ( val1 > val2 ) ? ( val1 ) : ( val2 ) )

#define LEFT_LINK_WITH_SAME_VAL( Node ) ( Node->left != nullptr && Node->left->val == Node->val )
#define RIGHT_LINK_WITH_SAME_VAL( Node ) ( Node->right != nullptr && Node->right->val == Node->val )

class Solution {

    int ExploreToEndNode( TreeNode* Node, int nDepthFromTop, int &nMaxSameValTreeDiameter ) {

		if( Node == nullptr ) return nDepthFromTop;

		int nLeftDepthFromRoot = 0;
		if( LEFT_LINK_WITH_SAME_VAL( Node ) ) nLeftDepthFromRoot = 1 + ExploreToEndNode( Node->left, nDepthFromTop + 1, nMaxSameValTreeDiameter );
		else ExploreToEndNode( Node->left, 0, nMaxSameValTreeDiameter );

		int nRightDepthFromRoot = 0;
		if( RIGHT_LINK_WITH_SAME_VAL( Node ) ) nRightDepthFromRoot = 1 + ExploreToEndNode( Node->right, nDepthFromTop + 1, nMaxSameValTreeDiameter );
		else ExploreToEndNode( Node->right, 0, nMaxSameValTreeDiameter );

		nMaxSameValTreeDiameter = FIND_MAX( nMaxSameValTreeDiameter, nLeftDepthFromRoot + nRightDepthFromRoot );
		return FIND_MAX( nLeftDepthFromRoot, nRightDepthFromRoot );
	}

public:
	int longestUnivaluePath( TreeNode *root ) {

		int nMaxSamValTreeDiameter = 0;
		ExploreToEndNode( root, 0, nMaxSamValTreeDiameter );

		return nMaxSamValTreeDiameter;
	}
};