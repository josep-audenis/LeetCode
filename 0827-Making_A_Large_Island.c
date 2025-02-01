// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
// 
// Return the size of the largest island in grid after applying this operation.
// 
// An island is a 4-directionally connected group of 1s.
// 
// - Example 1:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
// 
// - Example 2:
// Input: grid = [[1,1],[1,0]]
// Output: 4
// Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
// 
// - Example 3:
// Input: grid = [[1,1],[1,1]]
// Output: 4
// Explanation: Can't change any 0 to 1, only one island with area = 4.
//  
// Constraints:
// · n == grid.length
// · n == grid[i].length
// · 1 <= n <= 500
// · grid[i][j] is either 0 or 1.

typedef struct {
    int i;
    int j;
} point_t;

const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool isOutside(int i, int j, int maxR, int maxC) {   
    return (i < 0 || j < 0 || i >= maxR || j >= maxC);                      
}

int max(int v1, int v2) {
    return (v1 > v2 ? v1 : v2);
}

int min(int v1, int v2) {
    return (v1 < v2 ? v1 : v2);
}

int exploreIsland(int i, int j, int island_id, int **grid, int nrow, int ncol) {                        //explores an island starting from cell (i, j), assigns it a unique ID, and calculates its size
    int land_size = 0;  
    point_t queue[nrow * ncol]; 
    int front = 0, rear = 0;

    queue[rear++] = (point_t){i, j}; 
    grid[i][j] = island_id; 

    while (front < rear) {                                                                              //bfs to explore the entire island
        point_t p = queue[front++];
        land_size++;

        for (int d = 0; d < 4; ++d) {                                                                   //explore in 4 possible directions
            int ai = p.i + dirs[d][0];
            int aj = p.j + dirs[d][1];

            if (isOutside(ai, aj, nrow, ncol) || grid[ai][aj] != 1) continue;                           //if the cell is out of bounds or not land (1), skip it
            
            grid[ai][aj] = island_id;                                                                   //mark the cell as part of the island and 
            queue[rear++] = (point_t){ai, aj};                                                          //add it to the queue
        }
    }

    return land_size; 
}

int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int max_island = gridSize * (*gridColSize); 
    int *islands = (int *)malloc((max_island + 2) * sizeof(int)); 
    int island_id = 2; 
    int max_size = 1; 
    
    memset(islands, 0, max_island + 2); 


    for (int i = 0; i < gridSize; ++i) {                                                                //label all islands in the grid
        for (int j = 0; j < (*gridColSize); ++j) {
            if (grid[i][j] == 1) {                                                                      //if found unexplored land
                islands[island_id] = exploreIsland(i, j, island_id, grid, gridSize, *gridColSize);
                island_id++;                                                                            //increment the next island ID
            }
        }
    }

    if (island_id == 2) {                                                                               //if there are no islands, the best option is to turn one cell into land
        free(islands);
        return 1;
    }

    if (island_id == 3) {                                                                               //if there is only one island, we can expand it by one cell
        int the_land_size = islands[2] + 1;
        free(islands);
        return min(gridSize * (*gridColSize), the_land_size);
    }


    for (int i = 0; i < gridSize; ++i) {                                                                //see if it can connect adjacent islands
        for (int j = 0; j < (*gridColSize); ++j) {
            if (grid[i][j] != 0) continue;                                                              //only consider water cells

            int seen[island_id]; 
            int curr_size = 1; 
            memset(seen, 0, sizeof(seen));

            
            for (int d = 0; d < 4; d++) {                                                               //check neighboring islands in 4 directions
                int ai = i + dirs[d][0];
                int aj = j + dirs[d][1];

                
                if (isOutside(ai, aj, gridSize, (*gridColSize)) || grid[ai][aj] <= 1) continue;         //if out of bounds or not part of an island, skip it
                    
                int id = grid[ai][aj];                                                                  //id of the neighboring island
                if (seen[id] == 0) { 
                    curr_size += islands[id];                                                           //add its size
                    seen[id] = 1;                                                                       //mark it as counted
                }
            }
            max_size = max(max_size, curr_size);                                                        //update the largest island size
        }
    }
    free(islands); 

    return max_size; 
}


// Runtime: 630ms 
// Memory: 25.71MB