---
LeetCodeSeq: 1
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 9
LeetCode150ConceptOk: 9
LeetCode150TestPass: 9
LeetCode150Finish: 9
LeetCode150Review: 9
LeetCode150Rev2: 9
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 13
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### Concept
- 檢查連續數字用 O(n) 的方式
	- 所有 vector 裡面數值加到 set
	- 然後檢查 set 裡面的數值 num
		- **如果某個 num 是連續數字最小的那個 -> 開始往後檢查連續幾個數字**
		- 如果 num-1 存在於 set -> 跳過
		- 如果 num-1 不存在於 set -> num 是連續數字的第一個 -> 往後檢查

### Arrays & Hashing

| #   | Problem                                                                                          | Difficulty | Solution                                                           | Status                  | Review | Review2 | Note                                                                                                            |
| --- | ------------------------------------------------------------------------------------------------ | ---------- | ------------------------------------------------------------------ | ----------------------- | ------ | ------- | --------------------------------------------------------------------------------------------------------------- |
| 1   | [217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)                     | Easy       | [Link](https://neetcode.io/solutions/contains-duplicate)           | Finish 6/11             | 9/03   | 10/23   | [[217. Contains Duplicate - Main]]                                                                              |
| 2   | [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)                               | Easy       | [Link](https://neetcode.io/solutions/valid-anagram)                | Finish 6/11             | 9/03   | 10/23   | [[242. Valid Anagram - Main]]                                                                                   |
| 3   | [1. Two Sum](https://leetcode.com/problems/two-sum/)                                             | Easy       | [Link](https://neetcode.io/solutions/two-sum)                      | Finish 6/10             | 9/03   | 10/23   | [[1. Two Sum - Main]]                                                                                           |
| 4   | [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)                              | Medium     | [Link](https://neetcode.io/solutions/group-anagrams)               | Finish 6/12             | 9/12   | 10/23   | [[49. Group Anagrams - Main]]                                                                                   |
| 5   | [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)           | Medium     | [Link](https://neetcode.io/solutions/top-k-frequent-elements)      | Finish 6/13             | 9/12   | 10/23   | [[347. Top K Frequent Elements - Main]]                                                                         |
| 6   | [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | Medium     | [Link](https://neetcode.io/solutions/product-of-array-except-self) | Finish 6/13             | 9/12   | 10/27   | [[238. Product of Array Except Self - Main]] - **複習2nd - 會有點不順**                                                |
| 7   | [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)                                  | Medium     | [Link](https://neetcode.io/solutions/valid-sudoku)                 | Finish 6/13             | 9/13   | 10/27   | [[36. Valid Sudoku - Main]]                                                                                     |
| 8   | [271. Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/)       | Medium     | [Link](https://neetcode.io/solutions/encode-and-decode-strings)    | Finish 9/13 (Pass 8/16) | 9/13   | 10/27   | [[271. Encode and Decode Strings - Main]] - **string 操作需要複習和熟悉(1st) / encode + string 的題目仍然要多練習 (2nd)**         |
| 9   | [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) | Medium     | [Link](https://neetcode.io/solutions/longest-consecutive-se)       | Finish 6/13             | 9/13   | 11/09   | [[128. Longest Consecutive Sequence - Main]] - **unordered_set 使用 vector 初始化 + 查詢連續數字(1st)  / 仍然沒辦法直接想到 (2nd)** |
