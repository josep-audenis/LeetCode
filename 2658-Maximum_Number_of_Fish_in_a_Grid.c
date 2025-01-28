// You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
// · A land cell if grid[r][c] = 0, or
// · A water cell containing grid[r][c] fish, if grid[r][c] > 0.
// 
// A fisher can start at any water cell (r, c) and can do the following operations any number of times:
// · Catch all the fish at cell (r, c), or
// · Move to any adjacent water cell.
// 
// Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally, or 0 if no water cell exists.
// 
// An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.
// 
// - Example 1:
// Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
// Output: 7
// Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.
// 
// - Example 2:
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
// Output: 1
// Explanation: The fisher can start at cells (0,0) or (3,3) and collect a single fish. 
// 
// Constraints:
// · m == grid.length
// · n == grid[i].length
// · 1 <= m, n <= 10
// · 0 <= grid[i][j] <= 10

uint16_t max(uint16_t v1, uint16_t v2) {
    return (v1 < v2 ? v2 : v1);                                                                     //return max value from two integers
}

uint8_t getIndex(uint8_t i, uint8_t j, uint8_t size) {
    return (j + (i * size));                                                                        //converts 2d coordinates into a 1d array index
}

bool isOutside(uint8_t i, uint8_t j, uint8_t maxR, uint8_t maxC) {   
    return (i < 0 || j < 0 || i >= maxR || j >= maxC);                                              //check if cell is outside the matrix
}

uint16_t dfs(uint8_t gridSize, uint8_t gridColSize, int ** grid, bool * visited, uint8_t i, uint8_t j) {
    uint8_t index = getIndex(i, j, gridColSize);

    if (isOutside(i, j, gridSize, gridColSize) || grid[i][j] == 0 || visited[index]) return 0;      //don't count values outside the matrix, land cells, or visited cells

    visited[index] = true;

    return grid[i][j]                                       \
    + dfs(gridSize, gridColSize, grid, visited, i , j+1)    \
    + dfs(gridSize, gridColSize, grid, visited, i+1 , j)    \
    + dfs(gridSize, gridColSize, grid, visited, i , j-1)    \
    + dfs(gridSize, gridColSize, grid, visited, i-1 , j);                                           //return the value of the cell + the value of the adjacent cells
}

int findMaxFish(int** grid, int gridSize, int* gridColSize) {
    
    bool * visited = calloc(gridSize * (*gridColSize), sizeof(bool));

    uint16_t fish = 0;

    for (uint8_t i = 0; i < gridSize; i++) {
        for (uint8_t j = 0; j < *gridColSize; j++) {
            if (grid[i][j] > 0 && !visited[getIndex(i, j, *gridColSize)]) {
                fish = max(fish, dfs(gridSize, *gridColSize, grid, visited, i , j));                //get the max value of the current max fish count or the current cell possible max fish
            }
        }
    }
    return fish;
}

// Runtime: 0ms 
// Memory: 13.2MB