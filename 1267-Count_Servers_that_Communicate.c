// You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.
// 
// Return the number of servers that communicate with any other server.
// 
// - Example 1:
// Input: grid = [[1,0],[0,1]]
// Output: 0
// Explanation: No servers can communicate with others.
// 
// - Example 2:
// Input: grid = [[1,0],[1,1]]
// Output: 3
// Explanation: All three servers can communicate with at least one other server.
// 
// - Example 3:
// Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
// Output: 4
// Explanation: The two servers in the first row can communicate with each other. The two servers in the third column can communicate with each other. The server at right bottom corner can't communicate with any other server.
// 
// Constraints:
// · m == grid.length
// · n == grid[i].length
// · 1 <= m <= 250
// · 1 <= n <= 250
// · grid[i][j] == 0 or 1

int countServers(int** grid, int gridSize, int* gridColSize) {
    uint8_t n_rows[*gridColSize];   
    uint8_t n_cols[gridSize];

    memset(n_rows, 0, sizeof(n_rows));
    memset(n_cols, 0, sizeof(n_cols));

    int count = 0;

    for (uint8_t i = 0; i < gridSize; i++) {
        for (uint8_t j = 0; j < *gridColSize; j++) {
            if (grid[i][j]) {
                n_rows[j]++;
                n_cols[i]++;
            }
        }
    }

    for (uint8_t i = 0; i < gridSize; i++) {
        for (uint8_t j = 0; j < *gridColSize; j++) {
            if (grid[i][j] && (n_rows[j] > 1 || n_cols[i] > 1)) count++;
        }
    }

    return count;
}

// Runtime: 0ms 
// Memory: 13.2MB