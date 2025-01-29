// In this problem, a tree is an undirected graph that is connected and has no cycles.
// 
// You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
// 
// Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
// 
// - Example 1:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
// 
// - Example 2:
// Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
// Output: [1,4]
//  
// Constraints:
// · n == edges.length
// · 3 <= n <= 1000
// · edges[i].length == 2
// · 1 <= ai < bi <= edges.length
// · ai != bi
// · There are no repeated edges.
// · The given graph is connected.

int find(int* parent, int x) {                                                          //find the root of the set containing x using path compression
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);                                            //make the tree flatter
    }
    return parent[x];
}

void unionSet(int* parent, int* rank, int x, int y) {                                   //merge two sets using union by rank
    int rx = find(parent, x);                                                           //find root of x
    int ry = find(parent, y);                                                           //find root of y
    if (rx != ry) {
        if (rank[rx] > rank[ry]) {                                                      
            parent[ry] = rx;                                                            //merge if they belong to different sets by attaching the smaller tree to the larger one
        } else if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else {
            parent[ry] = rx;                                                            //if ranks are equal, choose one as root and increment its rank
            rank[rx]++;
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int* parent = (int*)malloc((edgesSize + 1) * sizeof(int));
    int* rank = (int*)calloc((edgesSize + 1), sizeof(int));
    
    for (int i = 1; i <= edgesSize; i++) {
        parent[i] = i;                                                                  //initialize the parent of each node to itself
    }
    
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 0; i < edgesSize; i++) {                                               //iterate through the edges to find the first one that forms a cycle
        int u = edges[i][0], v = edges[i][1];
        if (find(parent, u) == find(parent, v)) {                                       //if u and v already belong to the same set, adding this edge creates a cycle
            result[0] = u;
            result[1] = v;
        } else {
            unionSet(parent, rank, u, v);                                               //merge the sets
        }
    }
    
    free(parent);
    free(rank);
    return result;
}

// Runtime: 0ms 
// Memory: 9.56MB