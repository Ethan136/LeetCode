---
LeetCodeSeq: 4
LeetCode150Finish: 7
LeetCode150Num: 7
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150ConceptOk: 7
LeetCode150TestPass: 7
LeetCode150Review: 7
LeetCode150Rev2: 7
---
### 模板 - 線性檢查某個 array，無法馬上判斷的時候加到 stack 等後續再判斷

架構
- array[i] 擴增一個數值作為『ending trigger』
- for loop
	- 1）檢查當前 array[i] 能不能拿來判斷先前尚未處理的 penging index (存在 stack 裡面)
	- 2）當前 array[i] 加到 pending index

隱藏條件
- **順序性掃描，檢查 stack 裡面的資料有順序性，檢查到 stack top 不符合的情況下，stack under top 也一定不符合**

注意事項
- **除非很確定減少 push stack 可以很安全的減少後續判斷情況，不然一律 push to stack 會比較安全**
	- 比如：[[84. Largest Rectangle in Histogram - Main]]

題目
- [[20. Valid Parentheses - Main]]
- [[739. Daily Temperatures - Main]]
- [[853. Car Fleet - Main]]
- [[84. Largest Rectangle in Histogram - Main]]

### Stack

| #   | Problem                                                                                                  | Difficulty | Solution                                                               | Status      | Review | Review 2 | Note                                                                    |
| --- | -------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------------- | ----------- | ------ | -------- | ----------------------------------------------------------------------- |
| 21  | [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)                                | Easy       | [Link](https://neetcode.io/solutions/valid-parentheses)                | 6/15 Finish | 9/16   | 11/05    | [[20. Valid Parentheses - Main]] - *練習用模板來寫 (2nd)*                      |
| 22  | [155. Min Stack](https://leetcode.com/problems/min-stack/)                                               | Medium     | [Link](https://neetcode.io/solutions/min-stack)                        | 6/15 Finish | 9/16   | 11/05    | [[155. Min Stack - Main]]                                               |
| 23  | [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/) | Medium     | [Link](https://neetcode.io/solutions/evaluate-reverse-polish-notation) | 6/15 Finish | 9/16   | 11/05    | [[150. Evaluate Reverse Polish Notation - Main]]                        |
| 24  | [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)                          | Medium     | [Link](https://neetcode.io/solutions/generate-parentheses)             | 6/15 Finish | 9/16   | 11/05    | [[22. Generate Parentheses - Main]]                                     |
| 25  | [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)                             | Medium     | [Link](https://neetcode.io/solutions/daily-temperatures)               | 6/15 Finish | 9/16   | 11/05    | [[739. Daily Temperatures - Main]] - **要想好哪個是 pending 需要放到 stack（2nd）** |
| 26  | [853. Car Fleet](https://leetcode.com/problems/car-fleet/)                                               | Medium     | [Link](https://neetcode.io/solutions/car-fleet)                        | 6/15 Finish | 9/16   | 11/05    | [[853. Car Fleet - Main]] - *練習用模板來寫 (2nd)*                             |
| 27  | [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)      | Hard       | [Link](https://neetcode.io/solutions/largest-rectangle-in-histogram)   | 6/15 Finish | 9/16   | 11/06    | [[84. Largest Rectangle in Histogram - Main]] - *練習用模板來寫 (2nd)*         |
