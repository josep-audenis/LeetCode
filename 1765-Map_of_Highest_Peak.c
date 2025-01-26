// You are given an integer matrix isWater of size m x n that represents a map of land and water cells.
// · If isWater[i][j] == 0, cell (i, j) is a land cell.
// · If isWater[i][j] == 1, cell (i, j) is a water cell.
// 
// You must assign each cell a height in a way that follows these rules:
// · The height of each cell must be non-negative.
// · If the cell is a water cell, its height must be 0.
// · Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
// 
// Find an assignment of heights such that the maximum height in the matrix is maximized.
// Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
// 
// - Example 1:
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
// 
// - Example 2:
// Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
// Output: [[1,1,0],[0,1,1],[1,2,2]]
// Explanation: A height of 2 is the maximum possible height of any assignment.
// Any height assignment that has a maximum height of 2 while still meeting the rules will also be accepted.
//  
// Constraints:
// · m == isWater.length
// · n == isWater[i].length
// · 1 <= m, n <= 1000
// · isWater[i][j] is 0 or 1.
// · There is at least one water cell.

const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int isOutside(int i, int j, int maxR, int maxC) {
    return (i < 0 || j < 0 || i >= maxR || j >= maxC);                                      //check if cell is outside the matrix
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** highestPeak(int** isWater, int isWaterSize, int* isWaterColSize, int* returnSize, int** returnColumnSizes) {
    int r = isWaterSize;
    int c = *isWaterColSize;

    *returnSize = isWaterSize;
    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);

    int ** map = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        (*returnColumnSizes)[i] = *isWaterColSize;
        map[i] = malloc(c * sizeof(int));
        if (c > 1) {                                                                        //check size of column
            memset(map[i], 10000, sizeof(int) * c);                                         //set the entire matrix to maximum value
        } else {
            map[i][0] = 10000;
        }
    } 

    int minH, ai, aj, value;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (isWater[i][j]) {
                map[i][j] = 0;                                                              //set the water cells to 0 in the first iteration
                continue;
            }
            minH = (r*c) + 1;
            for (int d = 0; d < 4; d++) {                                                   //check all adjacent cells
                ai = i + dirs[d][0];
                aj = j + dirs[d][1];

                if (isOutside(ai, aj, r, c)) continue;
                
                value = (isWater[ai][aj] ? 0 : map[ai][aj]);                                //gets the value of the adjacent cell, if it's water sets 0 since it's the first iteration all values are 10000

                minH = (minH < value ? minH : value);                                       //gets the minimum value of all adjacent cells
            }

            map[i][j] = minH+1;                                                             //adds one the the minimum value of the adjacent cells
        }
    }

    for (int i = r - 1; i >= 0; i--) {                                                      //since in the first iteration there where no water cells and the values where all initialized at 10000
        for (int j = c - 1; j >= 0; j--) {                                                  //iterate a second time the matrix backwards to recalculate all values
            if (isWater[i][j]) continue;                                                    //don't want to touch water cells
            minH = (r*c) + 1;
            for (int d = 0; d < 4; d++) {                                                   //check adjacent cells
                ai = i + dirs[d][0];
                aj = j + dirs[d][1];

                if (isOutside(ai, aj, r, c)) continue;
                
                value = map[ai][aj];                                                        //now we don't care about water, because all water cells are correctly set

                minH = (minH < value ? minH : value);                                       //gets the minimum value of all adjacent cells                                    
            }

            map[i][j] = minH+1;
        }
    }

    return map;
}

// Runtime: 55ms 
// Memory: 171.08MB

//This is a very suboptimal solution, it would have been better to do a BFS with all the water squares first, but I wasn't in the mood...