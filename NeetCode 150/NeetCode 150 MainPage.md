---
Level: Main
Status: InProgress
StartDate: 2024-03-21
DueDate: 2024-06-21
FinishDate:
Urgency: "20"
tags:
  - leetcode
  - algorithm
ParentTask:
  - "[[刷題機制和策略規劃]]"
  - "[[2025換工作準備 Q3]]"
---

# NeetCode RoadMap
[Roadmap](https://neetcode.io/roadmap)

# NeetCode 150 Progress Tracker

```dataviewjs
// Get all files in the NeetCode 150 folder except this one
const pages = dv.pages('"'+this.current().file.folder+'"')
    .filter(p => p.file.name != this.current().file.name )
    .sort(p => p.NeetCodeSeq);

// Calculate total statistics
let totalProblems = 0;
let totalConceptOk = 0;
let totalTestPass = 0;
let totalCompleted = 0;
let totalReviewed = 0;
for (let page of pages) {
    totalProblems += page.LeetCodeNum || 0;
    totalConceptOk += page.LeetCodeConceptOk || 0;
	totalTestPass += page.LeetCodeTestPass || 0;
    totalCompleted += page.LeetCodeFinish || 0;
    totalReviewed += page.LeetCodeReview || 0;
}
const overallConceptOk = Math.round((totalConceptOk / totalProblems) * 100);
const overallTestPass = Math.round((totalTestPass / totalProblems) * 100);
const overallComplete = Math.round((totalCompleted / totalProblems) * 100);
const overallReview = Math.round((totalReviewed / totalProblems) * 100);

// Create a table with the information
const table = dv.markdownTable(
    ["Category", 
    "Problems ("+totalProblems.toString()+")", 
    "Concept " +totalConceptOk.toString() + " ("+overallConceptOk.toString()+"%)", 
    "TestPass " +totalTestPass.toString() + " ("+overallTestPass.toString()+"%)", 
    "Completed "+totalCompleted.toString()+ " ("+overallComplete.toString()+"%)", 
    "Reviewed " +totalReviewed.toString() + " ("+overallReview.toString()+"%)", 
    "NeetCodeSeq"],
    [
        ...pages.map(p => [
            p.file.link,
            p.LeetCodeNum || 0,
            (p.LeetCodeConceptOk || 0) + " (" + (p.LeetCodeNum ? Math.round((p.LeetCodeConceptOk || 0) / p.LeetCodeNum * 100) + '%' : '0%') + ")",
            (p.LeetCodeTestPass || 0) + " (" + (p.LeetCodeNum ? Math.round((p.LeetCodeTestPass || 0) / p.LeetCodeNum * 100) + '%' : '0%') + ")",
			(p.LeetCodeFinish || 0) + " (" + (p.LeetCodeNum ? Math.round((p.LeetCodeFinish || 0) / p.LeetCodeNum * 100) + '%' : '0%') + ")",
			(p.LeetCodeReview || 0) + " (" + (p.LeetCodeNum ? Math.round((p.LeetCodeReview || 0) / p.LeetCodeNum * 100) + '%' : '0%') + ")",
            p.NeetCodeSeq || ''
        ])
    ]
);

dv.header(3, "Progress Overview");
dv.paragraph(table);
``` 
