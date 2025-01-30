// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
// Divide the nodes of the graph into m groups (1-indexed) such that:
// · Each node in the graph belongs to exactly one group.
// · For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
// 
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
// 
// - Example 1:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
// 
// - Example 2:
// Input: n = 3, edges = [[1,2],[2,3],[3,1]]
// Output: -1
// Explanation: If we add node 1 to the first group, node 2 to the second group, and node 3 to the third group to satisfy the first two edges, we can see that the third edge will not be satisfied.
// It can be shown that no grouping is possible.
//  
// Constraints:
// · 1 <= n <= 500
// · 1 <= edges.length <= 104
// · edges[i].length == 2
// · 1 <= ai, bi <= n
// · ai != bi
// · There is at most one edge between any pair of vertices.

#define MAX_NODES 1000  

typedef struct {
    int data[MAX_NODES]; 
    int front, rear; 
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int value) {
    q->data[q->rear++] = value;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

bool isBipartite(int adj[MAX_NODES][MAX_NODES], int n, int node, int colors[]) {                    //check if a graph is bipartite using BFS
    Queue q;
    initQueue(&q);
    enqueue(&q, node);
    colors[node] = 0;  

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        for (int i = 0; i < n; i++) {
            if (adj[current][i]) {                                                                  //if an edge exists
                if (colors[i] == colors[current]) return false;                                     //a cycle with an odd number of nodes means it's not bipartite
                if (colors[i] == -1) { 
                    colors[i] = 1 - colors[current];                                                //assign opposite color
                    enqueue(&q, i);
                }
            }
        }
    }
    return true;
}


int getLongestShortestPath(int adj[MAX_NODES][MAX_NODES], int srcNode, int n) {                     //find the longest shortest path from a given source node
    Queue q;
    initQueue(&q);
    bool visited[MAX_NODES] = {false};
    enqueue(&q, srcNode);
    visited[srcNode] = true;
    int distance = 0; 

    while (!isEmpty(&q)) {
        int nodesLayer = q.rear - q.front;                                                          //number of nodes at current BFS level
        for (int i = 0; i < nodesLayer; i++) {
            int current = dequeue(&q);
            for (int j = 0; j < n; j++) {
                if (adj[current][j] && !visited[j]) { 
                    visited[j] = true;
                    enqueue(&q, j);
                }
            }
        }
        distance++;                                                                                 //move to the next BFS level
    }

    return distance;
}


int getNGroups(int adj[MAX_NODES][MAX_NODES], int node, int distances[], bool visited[], int n) {   //calculate the number of groups in a connected component
    visited[node] = true;
    int maxGroups = distances[node]; 

    for (int i = 0; i < n; i++) {
        if (adj[node][i] && !visited[i]) { 
            int neighbors = getNGroups(adj, i, distances, visited, n);
            if (neighbors > maxGroups) maxGroups = neighbors;                                       //keep track of the maximum depth in the component
        }
    }

    return maxGroups;
}

int magnificentSets(int n, int** edges, int edgesSize, int* edgesColSize) {
    int adj[MAX_NODES][MAX_NODES] = {0}; 
    int colors[MAX_NODES];
    int distances[MAX_NODES];
    bool visited[MAX_NODES];
    int maxGroups = 0;

    memset(colors, -1, sizeof(colors));                                                             //initialize all nodes as uncolored
    memset(visited, 0, sizeof(visited)); 

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0] - 1; 
        int v = edges[i][1] - 1;
        adj[u][v] = adj[v][u] = 1;                                                                  //undirected graph
    }
    
    for (int i = 0; i < n; i++) {                                                                   //check if the graph is bipartite
        if (colors[i] == -1) { 
            if (!isBipartite(adj, n, i, colors)) return -1; 
        }
    }

    for (int i = 0; i < n; i++) {
        distances[i] = getLongestShortestPath(adj, i, n);                                           //calculate longest shortest path for each node
    }

    for (int i = 0; i < n; i++) {       
        if (!visited[i]) maxGroups += getNGroups(adj, i, distances, visited, n);                    //calculate the number of groups in each connected component
    }
    
    return maxGroups;
}

// Runtime: 1136ms 
// Memory: 17.6MB