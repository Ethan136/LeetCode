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

#define DO_DIGIT_ADD( StoreValue, TakeValue, CarryDigit ) \
	StoreValue += ( TakeValue + CarryDigit );             \
	CarryDigit = 0;                                       \
                                                          \
	if( StoreValue >= 10 ) {                              \
		StoreValue -= 10;                                 \
		CarryDigit = 1;                                   \
	}

#define DO_DIGIT_ADD_AND_GO_NEXT_NODE( StoreNode, ValTakeNode, CarryDigit ) \
	DO_DIGIT_ADD( StoreNode->val, ValTakeNode->val, CarryDigit )            \
                                                                            \
                                                                            \
	StoreNode = StoreNode->next;                                            \
	ValTakeNode = ValTakeNode->next;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		
		// about 9 + 8 = 17 -> carry digit = 1
		int nCarryDigit = 0;

		// the resultant list
		ListNode *pResult = l1;

		// make fake head
		ListNode* pPrevl1;
		ListNode *pSpareNode = l2;

		// Step1: scan both list
		while( true ) {

			// do backup before add
			pPrevl1 = l1;

			// do add and go to next node
			DO_DIGIT_ADD_AND_GO_NEXT_NODE( l1, l2, nCarryDigit );

			// if l1 or l2 is empty
			if( ( l1 == nullptr ) || ( l2 == nullptr ) ) {
				break;
			}
		}

		// check whether l1 is at the end, snatch remained nodes of l2
		if( l1 == nullptr ) {
			pPrevl1->next = l2;
			l1 = l2;
		}

		// Step2: scan only l1
		while( l1 != nullptr ) {

			DO_DIGIT_ADD( l1->val, 0, nCarryDigit );

			pPrevl1 = l1;
			l1 = l1->next;
		}

		// if carry digit exist, augment l1
		if( nCarryDigit ) {
			pPrevl1->next = pSpareNode;
			pPrevl1->next->val = 1;
			pPrevl1->next->next = nullptr;
		}

		// return result
		return pResult;
    }
};
// @lc code=end

