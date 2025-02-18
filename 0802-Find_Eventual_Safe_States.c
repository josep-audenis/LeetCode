// There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
// 
// Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.
// 
// - Example 1:
// Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Output: [2,4,5,6]
// Explanation: The given graph is shown above.
// Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
// Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
// 
// - Example 2:
// Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
// Output: [4]
// Explanation:
// Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.
//  
// Constraints:
// · n == graph.length
// · 1 <= n <= 104
// · 0 <= graph[i].length <= n
// · 0 <= graph[i][j] <= n - 1
// · graph[i] is sorted in a strictly increasing order.
// · The graph may contain self-loops.
// · The number of edges in the graph will be in the range [1, 4 * 104].

bool dfs(int index, bool * visit, bool * stack, int ** graph, int n, int * nSafe, int * nCol) {
    if (stack[index]) return true;                                                                      //if the current node is in the recursion stack, a cycle is detected
    if (visit[index]) return false;                                                                     //if the node has already been visited and is not in a cycle
    
    *nSafe -= 1;                                                                                        //first assume that the node is not safe
    stack[index] = true;                                                                                //mark the current node as part of the recursion stack
    visit[index] = true;                                                                                //mark the current node as visited
    
    for (int i = 0; i < nCol[index]; i++) {                                                             //recursively check all neighbors of the current node    
        if (dfs(graph[index][i], visit, stack, graph, n, nSafe, nCol)) return true;                     //and return if any neighbor leads to a cycle
    }
    
    *nSafe += 1;                                                                                        //if no cycle is detected, mark the node as safe
    stack[index] = false;                                                                               //remove the current node from the recursion stack
    
    return false;                                                                                       //no cycle detected
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    int n = graphSize;
    *returnSize = graphSize;
    bool * visit = malloc(sizeof(bool) * n);
    bool * stack = malloc(sizeof(bool) * n);                                                            //array to track nodes in the current recursion stack
    memset(visit, 0, sizeof(bool) * n);
    memset(stack, 0, sizeof(bool) * n);

    for (int i = 0; i < n; i++) {
        dfs(i, visit, stack, graph, n, returnSize, graphColSize);                                       //perform dfs for each node to determine if it is part of a cycle
    }

    int * safe = malloc(sizeof(int) * *returnSize);                                                     
    int index = 0;
    for (int i = 0; i < n; i++) {
    if (!stack[i]) {                                                                                    //check if the node is not in the recursion stack
        safe[index] = i;                                                                                //construct the safe nodes array that will be returned
            index++;                                                                                    //add the safe node to the result array
        }
    }
    return safe;
}

// Runtime: 4ms 
// Memory: 23.90MB