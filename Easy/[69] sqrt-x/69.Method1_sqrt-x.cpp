/*
 * @lc app=leetcode id=69 lang=cpp
 *
 * [69] Sqrt(x)
 */

// @lc code=start

class Solution {
public:
    int mySqrt(int x) {

		// initial condition
		int nSolTry = 0;
		while( true ) {

			// try a square number
			if( nSolTry * nSolTry == x ) {
				return nSolTry;
			}

			// check if ( nSolTry + 1 )^2 > x
			// i.e. nSquareTry + 2 * nSolTry + 1 > x
			// i.e. nSquareTry > x - 2 * nSolTry - 1
			if( ( nSolTry * nSolTry > ( x - 2 * nSolTry - 1 ) ) ) {
				return nSolTry;
			}

			// try next solution
			nSolTry++;
		}
    }
};
// @lc code=end

