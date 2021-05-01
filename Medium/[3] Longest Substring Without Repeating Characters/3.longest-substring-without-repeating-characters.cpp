/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

// @lc code=start

#define MAX_NUM_OF_CHAR		( 255 )
#define INDEX_BEFORE_FISRT	( -1 )
#define FIND_MAX( value1, value2 )	( value1 > value2 ? value1 : value2 )
class Solution {
public:
    int lengthOfLongestSubstring(string s) {

		// initialize a recorder
		int nIndexList[ MAX_NUM_OF_CHAR ];
		for( int i = 0; i < MAX_NUM_OF_CHAR; i++ ) {
			nIndexList[ i ] = INDEX_BEFORE_FISRT;
		}

		// the overall and current sub str length
		int nSubStringLeftIndex = INDEX_BEFORE_FISRT;
		int nMaxSubStrLength = 0;

		// scan through the string
		for( int i = 0; i < s.length(); i++ ) {

			// if the char has been appeared
			if( nIndexList[ s[i] ] >= nSubStringLeftIndex ) {

				// (1) calc current substring length and record
				nMaxSubStrLength = FIND_MAX( i - nSubStringLeftIndex, nMaxSubStrLength );

				// (2) set new sub string
				nSubStringLeftIndex = nIndexList[ s[ i ] ] + 1;
				nIndexList[ s[ i ] ] = i;
				continue;
			}

			// if the current index is the last one
			if( i == s.length() - 1 ) {
				nMaxSubStrLength = FIND_MAX( s.length() - nSubStringLeftIndex, nMaxSubStrLength );
				break;
			}

			// if the char did not appear yet
			nIndexList[ s[i] ] = i;
		}

		return nMaxSubStrLength;
    }

};
// @lc code=end

