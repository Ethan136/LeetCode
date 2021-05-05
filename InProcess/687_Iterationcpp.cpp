enum ExploreState {
	STATE_TrasverseToEnd,
	STATE_AtEndOfTrasverse,
	STATE_ShiftToNextLayer,
	STATE_BackToPrevLayer,
	STATE_GoToPrevDivertNode,
	STATE_Finish,
};

enum ENodeType {
	ENodeType_Null,
	ENodeType_Leaf,
	ENodeType_LinkLeft,
	ENodeType_LinkRight,
	ENodeType_Root,
};

struct TNodeTrasverse {
	int nDepthFromTopBeforeTrasverse;
	vector<TreeNode*> DivertNode;
	TNodeTrasverse( int nDepth = 0 ) : nDepthFromTopBeforeTrasverse( nDepth ) {};
};

#define FIND_MAX( val1, val2 ) ( ( val1 > val2 ) ? ( val1 ) : ( val2 ) )

class Solution {

	ENodeType TrimNodeToSameValLink( TreeNode *root, vector< TreeNode * > &DiffValNodeCollect, int &nDivertNodeNum )
	{
		// node null
		if( root == nullptr )
			return ENodeType_Null;

		// if left node has same value
		if( ( root->left != nullptr ) && ( root->left->val == root->val ) ) {

			// left with same value but right not exist
			if( root->right == nullptr ) {
				return ENodeType_LinkLeft;
			}

			// left with same value but right has different one
			if( root->right->val != root->val ) {

				if( nDivertNodeNum >= DiffValNodeCollect.size() ) DiffValNodeCollect.push_back( root->right );
				else DiffValNodeCollect[ nDivertNodeNum ] = root->right;
				nDivertNodeNum++;

				return ENodeType_LinkLeft;
			}

			// left with same value and so as right node
			return ENodeType_Root;
		}

		// left exist but has different value
		if( root->left != nullptr ) {
			if( nDivertNodeNum >= DiffValNodeCollect.size() ) DiffValNodeCollect.push_back( root->left );
			else DiffValNodeCollect[ nDivertNodeNum ] = root->left;
			nDivertNodeNum++;
		}

		// right null
		if( root->right == nullptr ) {
			return ENodeType_Leaf;
		}

		// right with diff value
		if( root->right->val != root->val ) {
			if( nDivertNodeNum >= DiffValNodeCollect.size() ) DiffValNodeCollect.push_back( root->right );
			else DiffValNodeCollect[ nDivertNodeNum ] = root->right;
			nDivertNodeNum++;
	
			return ENodeType_Leaf;
		}

		// right node with same value, left node is empty
		return ENodeType_LinkRight;
	}

	int FindMaxPathSize( TreeNode *root, vector<TNodeTrasverse> &TrasverseRecord, int &nTrasverseRecordNum, vector< TreeNode * > &DiffValNodeCollect, int &nDivertNodeNum )
	{
		// 2D stack, to store the divert node with same val as root
		// here use the val of node to store the length from the toppest node (origin root)
		if( TrasverseRecord.size() < 1 ) TrasverseRecord.push_back( TNodeTrasverse( 0 ) );
		nTrasverseRecordNum = 1;

		// 1D stack, Before shift to next layer and restart a new left-trasverse
		// record the length below "the node which diverts to next layer"
		vector< int > LengthBelowDivertNodeInPrevLayer;

		// some operation info
		int nExploreState = STATE_TrasverseToEnd;
		int nLengthFromPrevDivertNode = 0;
		int nLengthFromTop = 0;

		// the resultant data
		int nMaxDiameter = 0;
		while( nExploreState != STATE_Finish ) {

			switch( nExploreState ) {

			case STATE_TrasverseToEnd: {

				switch( TrimNodeToSameValLink( root, DiffValNodeCollect, nDivertNodeNum ) ) {

				case ENodeType_Leaf:
					nExploreState = STATE_AtEndOfTrasverse;
					break;

				case ENodeType_Root:

					// modify the value definition as length from previous node and record divert node with same value
					root->val = nLengthFromTop;
					TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.push_back( root );

					// go along left side and record path length
					// re-start to count the length from this node
					root = root->left;
					nLengthFromPrevDivertNode = 1;
					nLengthFromTop++;
					break;

				case ENodeType_LinkLeft:
					// go along left side and record path length
					root = root->left;
					nLengthFromPrevDivertNode++;
					nLengthFromTop++;
					break;
				
				case ENodeType_LinkRight:
					// go along right side and record path length
					root = root->right;
					nLengthFromPrevDivertNode++;
					nLengthFromTop++;
					break;

				default:
					return 0;
				}
				break;
			}
			case STATE_AtEndOfTrasverse: {

				// update max diameter with the length from top to current end node
				nMaxDiameter = FIND_MAX( nMaxDiameter, nLengthFromTop );

				// if there's no previous divert node
				// pop out the stack of "current layer" and go back to previous layer
				if( TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.size() == 0 ) {
					nExploreState =  STATE_BackToPrevLayer;
					break;
				}

				// if there's a previous divert node in current layer
				// then the "previous divert node" must connect to next layer
				nExploreState = STATE_ShiftToNextLayer;
				break;
			}
			case STATE_ShiftToNextLayer: {
				// record the path length below the divert node
				LengthBelowDivertNodeInPrevLayer.push_back( nLengthFromPrevDivertNode );

				// shift to the next layer to begin a new left-trasverse
				// the new "top root" locates on the "next right node" of the divert node
				root = TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back()->right;
				nLengthFromTop = TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back()->val + 1;
				nLengthFromPrevDivertNode = 1;

				// add a new stack for new layer of left-trasverse
				// set current divert node as the head of the new layer
				if( nTrasverseRecordNum >= TrasverseRecord.size() ) {
					TrasverseRecord.push_back( TNodeTrasverse( TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back()->val ) );
				}
				else {
					TrasverseRecord[ nTrasverseRecordNum ] = TNodeTrasverse( TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back()->val );
				}
				nTrasverseRecordNum++;

				// start to left trasverse
				nExploreState = STATE_TrasverseToEnd;
				break;
			}
			case STATE_BackToPrevLayer: {

				// pop out the stack for the current layer
				nTrasverseRecordNum--;

				// if there is no ""previous layer
				if( nTrasverseRecordNum <= 0 ) {
					nExploreState = STATE_Finish;
					break;
				}

				// update the max diameter in the perspecitve of "the divert node on the top of stack"
				// check whether "left below length" + "right below length (i.e. the current length from prev divert node)" > recorded nMaxDiameter
				nMaxDiameter = FIND_MAX( nMaxDiameter, LengthBelowDivertNodeInPrevLayer.back() + nLengthFromPrevDivertNode );

				// update the "max length" below the divert node in the previous layer
				// length from prev divert node "in prev layer" = max( recorded length from prev divert node in "prev layer", length from prev divert node in "current layer" )
				nLengthFromPrevDivertNode = FIND_MAX( LengthBelowDivertNodeInPrevLayer.back(), nLengthFromPrevDivertNode  );

				// clear the length info of the previous node which saved "Before" advencing to the current layer
				LengthBelowDivertNodeInPrevLayer.pop_back();

				// after being back to the previous node, go to the previous divert node
				nExploreState = STATE_GoToPrevDivertNode;
				break;
			}

			case STATE_GoToPrevDivertNode: {

				// once back to the previous layer, "go upward" along the previous divert node
				TreeNode *pLastDivertNodeToDiscard = TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back();
				TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.pop_back();

				// once back to the previous layer, try to "go upward" along the previous divert node
				if( TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.size() ) {
					nLengthFromPrevDivertNode += pLastDivertNodeToDiscard->val - TrasverseRecord[ nTrasverseRecordNum - 1 ].DivertNode.back()->val;
					nExploreState = STATE_AtEndOfTrasverse;
					break;
				}

				// if there is no "previous divert node" -> use head to update info
				// the previous divert node locates in previous layer
				nLengthFromPrevDivertNode += pLastDivertNodeToDiscard->val - TrasverseRecord[ nTrasverseRecordNum - 1 ].nDepthFromTopBeforeTrasverse;
				nExploreState = STATE_BackToPrevLayer;
				break;
			}
			default:
				break;
			}
		}

		return nMaxDiameter;
	}

public:
	int longestUnivaluePath( TreeNode *root )
	{
		vector<TNodeTrasverse> TrasverseRecord;
		int nTrasverseRecordNum = 0;

		vector< TreeNode * > DivertNodeRecord;
		DivertNodeRecord.push_back( root );
		int nDivertNodeNum = 1;

        int nMaxPathSizeOfRoot = 0;
		int nMaxPathSize = 0;
		while( nDivertNodeNum > 0 ) {
			root = DivertNodeRecord[ --nDivertNodeNum ];
			nMaxPathSizeOfRoot = FindMaxPathSize( root, TrasverseRecord, nTrasverseRecordNum, DivertNodeRecord, nDivertNodeNum );
			nMaxPathSize = FIND_MAX( nMaxPathSize, nMaxPathSizeOfRoot );
		}
		return nMaxPathSize;
	}
};

// [1,1,null,1,1,1,null,1,1,null,null,1,null,1,1]