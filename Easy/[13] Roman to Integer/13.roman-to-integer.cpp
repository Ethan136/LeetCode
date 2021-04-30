/*
 * @lc app=leetcode id=13 lang=cpp
 *
 * [13] Roman to Integer
 */

// @lc code=start

// normal cases
#define NUM_OF_I	( 1 )
#define NUM_OF_V	( 5 )

#define NUM_OF_X	( 10 )
#define NUM_OF_L	( 50 )

#define NUM_OF_C	( 100 )
#define NUM_OF_D	( 500 )

#define NUM_OF_M	( 1000 )

// special cases
#define NUM_OF_IV	( 4 )
#define NUM_OF_IX	( 9 )

#define NUM_OF_XL	( 40 )
#define NUM_OF_XC	( 90 )

#define NUM_OF_CD	( 400 )
#define NUM_OF_CM	( 900 )

// scan step
#define ONE_SCAN_STEP	( 1 )

class Solution {
public:
	int romanToInt( string s )
	{
		// resultant value
		int nResult = 0;

		// do convertion
		int i = 0;
		while( s[ i ] != '\0' ) {

			// scan current word
			switch( s[ i ] ) {

			// check IV and IX
			case 'I':

				switch( s[ i + 1 ] ) {
				case 'V':
					nResult += NUM_OF_IV;
					i += ONE_SCAN_STEP;
					break;
				case 'X':
					nResult += NUM_OF_IX;
					i += ONE_SCAN_STEP;
					break;
				default:
					nResult += NUM_OF_I;
					break;
				}
				break;

			case 'V':
				nResult += NUM_OF_V;
				break;

			// check XL and XC
			case 'X':

				switch( s[ i + 1 ] ) {
				case 'L':
					nResult += NUM_OF_XL;
					i += ONE_SCAN_STEP;
					break;
				case 'C':
					nResult += NUM_OF_XC;
					i += ONE_SCAN_STEP;
					break;
				default:
					nResult += NUM_OF_X;
					break;
				}
				break;

			case 'L':
				nResult += NUM_OF_L;
				break;

			// check CD and CM
			case 'C':

				switch( s[ i + 1 ] ) {
				case 'D':
					nResult += NUM_OF_CD;
					i += ONE_SCAN_STEP;
					break;
				case 'M':
					nResult += NUM_OF_CM;
					i += ONE_SCAN_STEP;
					break;
				default:
					nResult += NUM_OF_C;
					break;
				}
				break;

			case 'D':
				nResult += NUM_OF_D;
				break;

			case 'M':
				nResult += NUM_OF_M;
				break;

			default:
				break;
			}

			// scan to next word
			i += ONE_SCAN_STEP;
		}

		return nResult;
	}
};
// @lc code=end

