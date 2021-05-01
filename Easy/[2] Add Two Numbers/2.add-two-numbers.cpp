/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#define DO_DIGIT_ADD( StoreValue, AddValue, CarryDigit )											\
					StoreValue += ( AddValue + CarryDigit );										\
					CarryDigit = 0;																	\
																									\
					if( StoreValue >= 10 ) {															\
						StoreValue -= 10;															\
						CarryDigit = 1;																\
					};

#define PREPARE_TO_RETURN
enum ESCAN_STATE {
	STATE_SCAN_BOTH_LIST,
	STATE_SNATCH_REMAINED_VALUE_TAKE_LIST_TO_STORE_LIST,
	STATE_SCAN_TO_LAST_OF_VALUE_TAKE_LIST,
	STATE_ONLY_SCAN_STORE_LIST,
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		
		// about 9 + 8 = 17 -> carry digit = 1
		int nCarryDigit = 0;

		// set one list to store and the other to take value
		ListNode *pStoreNode = l1;
		ListNode *pValueTakeNode = l2;

		// the spared node in case there's any need to expand the list
		ListNode *pSpareNode;

		// the resultant list
		ListNode *pResult = pStoreNode;

		// do scanning
		int nScanState = STATE_SCAN_BOTH_LIST;
		while( true ) {

			switch( nScanState ) {
			case STATE_SCAN_BOTH_LIST:

				// based on the constrains of the problem: the least length of l1 and l2 should be 1
				// os there's no need to prevent the condition that l1 == null or l2 == null

				// if the store list comes to the end
				if( pStoreNode->next == nullptr ) {
					nScanState = STATE_SNATCH_REMAINED_VALUE_TAKE_LIST_TO_STORE_LIST;
					break;
				}

				// if the take value list comes to the end
				if( pValueTakeNode->next == nullptr ) {
					nScanState = STATE_SCAN_TO_LAST_OF_VALUE_TAKE_LIST;
					break;
				}

				// add value
				DO_DIGIT_ADD( pStoreNode->val, pValueTakeNode->val, nCarryDigit );

				// advance to next node
				pStoreNode = pStoreNode->next;
				pValueTakeNode = pValueTakeNode->next;
				break;

			case STATE_SNATCH_REMAINED_VALUE_TAKE_LIST_TO_STORE_LIST:

				// link to the other list
				pStoreNode->next = pValueTakeNode->next;

				// set the current node of the other list as "last node"
				pValueTakeNode->next = nullptr;

				// advance to single list scan operation
				nScanState = STATE_SCAN_TO_LAST_OF_VALUE_TAKE_LIST;
				break;

			case STATE_SCAN_TO_LAST_OF_VALUE_TAKE_LIST:

				// add value
				DO_DIGIT_ADD( pStoreNode->val, pValueTakeNode->val, nCarryDigit );

				// spare the last value take node in case there's any need for augmentation
				pSpareNode = pValueTakeNode;
				pSpareNode->val = 0;

				// if the next store node is empty
				if( pStoreNode->next == nullptr ) {

					// if carry digit exist
					if( nCarryDigit ) {
						pSpareNode->val = nCarryDigit;
						pStoreNode->next = pSpareNode;
					}

					// return result
					return pResult;
				}

				// advance to next of store node
				pStoreNode = pStoreNode->next;

				// advance to single list scan operation
				nScanState = STATE_ONLY_SCAN_STORE_LIST;
				break;

			case STATE_ONLY_SCAN_STORE_LIST:

				// if there's no carry digit
				if( nCarryDigit == 0 ) {
					return pResult;
				}

				// add value
				DO_DIGIT_ADD( pStoreNode->val, 0, nCarryDigit );

				// if the next store node is empty
				if( pStoreNode->next == nullptr ) {

					// if carry digit exist
					if( nCarryDigit ) {
						pSpareNode->val = nCarryDigit;
						pStoreNode->next = pSpareNode;
					}

					// return result
					return pResult;
				}

				// go to next node
				pStoreNode = pStoreNode->next;
				break;

			}
		}
    }
};
// @lc code=end

