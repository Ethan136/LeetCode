/*
 * @lc app=leetcode id=69 lang=cpp
 *
 * [69] Sqrt(x)
 */

// @lc code=start

#define SOL_MAX					( 46340 )		// sqrt( 2^31 - 1 ) = 46340.xxx
#define SQUARE( value )			( value * value )

class Solution {
public:
    int mySqrt(int x) {

		// local variables
		int nLeft, nSolTry, nRight;

		// initial condition
		if( x * 0.5 < SOL_MAX ) {
			nLeft = 0;
			nSolTry = x * 0.5;
			nRight = x;
		}
		else {
			nLeft = 0;
			nSolTry = SOL_MAX * 0.5;
			nRight = SOL_MAX;
		}

		// calculate sqrt
		while( true ) {

			// try a square number
			if( SQUARE( nSolTry ) == x ) {
				return nSolTry;
			}

			// if more
			if( SQUARE( nSolTry ) > x ) {
				nRight = nSolTry - 1;
				nSolTry = ( nLeft + nRight ) * 0.5;
				continue;
			}

			// less, but add one more will exceed x -> sol
			if( SQUARE( nSolTry ) > x - 2 * nSolTry - 1 ) {
				return nSolTry;
			}

			// if less
			else {
				nLeft = nSolTry + 1;
				nSolTry = ( nLeft + nRight ) * 0.5;
				continue;
			}
		}
    }
};
// @lc code=end

