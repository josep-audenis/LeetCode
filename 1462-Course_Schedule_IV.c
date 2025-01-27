// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course ai first if you want to take course bi.
// For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.
// Prerequisites can also be indirect. If course a is a prerequisite of course b, and course b is a prerequisite of course c, then course a is a prerequisite of course c.
// You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should answer whether course uj is a prerequisite of course vj or not.
// 
// Return a boolean array answer, where answer[j] is the answer to the jth query.
// 
// - Example 1:
// Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
// Output: [false,true]
// Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
// Course 0 is not a prerequisite of course 1, but the opposite is true.
// 
// - Example 2:
// Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
// Output: [false,false]
// Explanation: There are no prerequisites, and each course is independent.
// 
// - Example 3:
// Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
// Output: [true,true]
//  
// Constraints:
// · 2 <= numCourses <= 100
// · 0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
// · prerequisites[i].length == 2
// · 0 <= ai, bi <= numCourses - 1
// · ai != bi
// · All the pairs [ai, bi] are unique.
// · The prerequisites graph has no cycles.
// · 1 <= queries.length <= 104
// · 0 <= ui, vi <= numCourses - 1
// · ui != vi

bool isPrerequisite(int numCourses, int * adjSize, int ** adjacent, bool * visited, int origin, int destination) {

    visited[origin] = true;

    if (origin == destination) return true;

    bool prerequisite = false;

    for (int i = 0; i < adjSize[origin]; i++) {                                                             //iterate over all adjacent nodes of the current node
        int current = adjacent[origin][i];
        if (!visited[current]) {                                                                            //if the adjacent node is not visited, perform a recursive dfs
            prerequisite = prerequisite || isPrerequisite(numCourses, adjSize, adjacent, visited, current, destination);
        } 
    }

    return prerequisite;                                                                                    //return true if any path to the destination is found; otherwise, false
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkIfPrerequisite(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    
    int ** adjacent = malloc(sizeof(int *) * numCourses);
    int * adjSize = calloc(numCourses, sizeof(int));

    for (int i = 0; i < prerequisitesSize; i++) {                                                           //build the adjacency list from the prerequisites input
        int firstCourse = prerequisites[i][0];
        if (adjSize[firstCourse] == 0) adjacent[firstCourse] = malloc(sizeof(int) * numCourses);
        adjacent[firstCourse][adjSize[firstCourse]++] = prerequisites[i][1];
    }

    bool * answer = malloc(sizeof(bool) * queriesSize);
    int index = 0;
    *returnSize = queriesSize;
    for (int i = 0; i < queriesSize; i++) {
        bool * visited = calloc(numCourses, sizeof(bool));
        answer[index++] = isPrerequisite(numCourses, adjSize, adjacent, visited, queries[i][0], queries[i][1]); //check if there is a path between the origin and destination in the current query
        free(visited);
    }
    return answer;
}

// Runtime: 225ms 
// Memory:  43.2MB