---
Level: Main
Status: InProgress
FinishDate:
StartDate: 2025-12-12
Urgency: "20"
tags:
  - leetcode
  - algorithm
ParentTask:
  - "[[刷題機制和策略規劃]]"
---

# NeetCode RoadMap
[Roadmap](https://neetcode.io/roadmap)

# NeetCode 250 Progress Tracker
```dataviewjs
// Get all files in the NeetCode 150 folder except this one
const pages = dv.pages('"'+this.current().file.folder+'"')
    .filter(p => ( (p.file.name != this.current().file.name) && (p.LeetCode250Num) ) )
    .sort(p => p.LeetCodeSeq);

// Calculate total statistics
let totalProblems = 0;
let totalConceptOk = 0;
let totalTestPass = 0;
let totalCompleted = 0;
let totalReviewed = 0;
let totalReviewed2 = 0;
for (let page of pages) {
    totalProblems += page.LeetCode250Num || 0;
    totalConceptOk += page.LeetCode250ConceptOk || 0;
	totalTestPass += page.LeetCode250TestPass || 0;
    totalCompleted += page.LeetCode250Finish || 0;
    totalReviewed += page.LeetCode250Review || 0;
    totalReviewed2 += page.LeetCode250Rev2 || 0;
}
const overallConceptOk = Math.round((totalConceptOk / totalProblems) * 100);
const overallTestPass = Math.round((totalTestPass / totalProblems) * 100);
const overallComplete = Math.round((totalCompleted / totalProblems) * 100);
const overallReview = Math.round((totalReviewed / totalProblems) * 100);
const overallReview2 = Math.round((totalReviewed2 / totalProblems) * 100);

// Create a table with the information
const table = dv.markdownTable(
    ["Category", 
    "Problems ("+totalProblems.toString()+")", 
    "Concept " +totalConceptOk.toString() + " ("+overallConceptOk.toString()+"%)", 
    "TestPass " +totalTestPass.toString() + " ("+overallTestPass.toString()+"%)", 
    "Completed "+totalCompleted.toString()+ " ("+overallComplete.toString()+"%)", 
    "Reviewed " +totalReviewed.toString() + " ("+overallReview.toString()+"%)", 
    "Reviewed2 " +totalReviewed2.toString() + " ("+overallReview2.toString()+"%)", 
    "NeetCodeSeq"],
    [
        ...pages.map(p => [
            p.file.link,
            p.LeetCode250Num || 0,
            (p.LeetCode250ConceptOk || 0) + " (" + (p.LeetCode250Num ? Math.round((p.LeetCode250ConceptOk || 0) / p.LeetCode250Num * 100) + '%' : '0%') + ")",
            (p.LeetCode250TestPass || 0) + " (" + (p.LeetCode250Num ? Math.round((p.LeetCode250TestPass || 0) / p.LeetCode250Num * 100) + '%' : '0%') + ")",
			(p.LeetCode250Finish || 0) + " (" + (p.LeetCode250Num ? Math.round((p.LeetCode250Finish || 0) / p.LeetCode250Num * 100) + '%' : '0%') + ")",
			(p.LeetCode250Review || 0) + " (" + (p.LeetCode250Num ? Math.round((p.LeetCode250Review || 0) / p.LeetCode250Num * 100) + '%' : '0%') + ")",
			(p.LeetCode250Rev2 || 0) + " (" + (p.LeetCode250Num ? Math.round((p.LeetCode250Rev2 || 0) / p.LeetCode250Num * 100) + '%' : '0%') + ")",
            p.LeetCodeSeq || ''
        ])
    ]
);

dv.header(3, "Progress Overview");
dv.paragraph(table);
``` 
