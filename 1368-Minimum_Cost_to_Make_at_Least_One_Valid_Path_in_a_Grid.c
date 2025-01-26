// Given an m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
// · 1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
// · 2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
// · 3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
// · 4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
// 
// Notice that there could be some signs on the cells of the grid that point outside the grid.
// You will initially start at the upper left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path does not have to be the shortest.
// You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.
// 
// Return the minimum cost to make the grid have at least one valid path.
// 
// - Example 1:
// Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
// Output: 3
// Explanation: You will start at point (0, 0).
// The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
// The total cost = 3.
// 
// - Example 2:
// Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
// Output: 0
// Explanation: You can follow the path from (0, 0) to (2, 2).
// 
// - Example 3:
// Input: grid = [[1,2],[4,3]]
// Output: 1
// 
// Constraints:
// · m == grid.length
// · n == grid[i].length
// · 1 <= m, n <= 100
// · 1 <= grid[i][j] <= 4

const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int isOutside(int i, int j, int maxC, int maxR) {
    return (i < 0 || j < 0 || i >= maxR || j >= maxC);                  //check if coordinates are outside the matrix
}

uint32_t pack(int c, int i, int j) {
    return ((uint32_t) c << 16)| (i << 8) | j;                          //pack cost and coordinates in a single 32 bytes unsigned integer
}

int * unpack(uint32_t packed) {                                         //unpack the cost and coordinates in an integer array
    int * cords = malloc(sizeof(int) * 3);
    cords[0] = packed >> 16;
    cords[1] = (packed >> 8) & 255;
    cords[2] = packed & 255;
    return cords;
} 

int minCost(int** grid, int gridSize, int* gridColSize) {
    int numRows = gridSize;
    int numCols = gridColSize[0];
    
    int front = 0, back = 0;

    int maxSize = numCols*numRows;

    uint32_t queue[maxSize];
    uint32_t minCost[numRows][numCols];

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            minCost[i][j] = 255;                                        //Initialize the minimum cost matrix with the maximum possible cost
        }
    }

    queue[back++] = pack(0, 0, 0);
    minCost[0][0] = 0;

    while(front != back) {                                              //while the queue is not empty
        
        int * info = unpack(queue[front++]);

        if (front >= maxSize) front -= maxSize;                         //make the queue array circular

        int cost = info[0];
        int i = info[1];
        int j = info[2];
        free(info);

        if (i == (numRows - 1) && j == (numCols - 1)) return cost;      //arrived at the last bottom right cell of the matrix (the end)

        int direction = grid[i][j];
        
        for (int k = 0; k < 4; k++) {                                   //check adjacent cells
            int ai = i + dirs[k][0];
            int aj = j + dirs[k][1];

            if (isOutside(ai, aj, numCols, numRows)) continue;

            int aCost = cost + (k + 1 != direction);                    //if the direction of the cell is different to the adjacent cell relative position, add 1 to the cost

            if (aCost < minCost[ai][aj]) {                              
                minCost[ai][aj] = aCost;
                if (k + 1 == direction) {                               //check if the direction of the cell is equal to the adjacent cell relative position
                    if (front == 0) front = maxSize;                    //make the queue array circular
                    queue[--front] = pack(aCost, ai, aj);               //add cell to the front
                } else {
                    queue[back++] = pack(aCost, ai, aj);                //add cell to the back
                    if (back >= maxSize) back -= maxSize;               //make the queue array circular
                }
            }
        }
    }
    
    return -1;
}

// Runtime: 24ms 
// Memory: 15.86MB