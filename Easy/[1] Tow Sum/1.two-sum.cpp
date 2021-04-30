/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

		// total length
		int nLength = nums.size();

		// loop related temporary variables
		int nSecondTarget;
		for( int i = 0; i < nLength; i++ ) {

			// set the second target
			nSecondTarget = target - nums[ i ];

			// try to find the second solution
			for( int j = i + 1; j < nLength; j++ ) {
				
				// if the solution has been found
				if( nums[ j ] == nSecondTarget ) {

					// use input vector as output container
					nums.clear();
					nums.push_back( i );
					nums.push_back( j );
					return nums;
				}
			}
		}

		// clear input and set as output
		nums.clear();
		return nums;
    }
};
// @lc code=end

