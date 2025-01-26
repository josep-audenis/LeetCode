// You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
// Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
// Return the smallest index i at which either a row or a column will be completely painted in mat.
//
// - Example 1:
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
//
// - Example 2:
// Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
// Output: 3
// Explanation: The second column becomes fully painted at arr[3].
//
// Constraints:
// · m == mat.length
// · n = mat[i].length
// · arr.length == m * n
// · 1 <= m, n <= 105
// · 1 <= m * n <= 105
// · 1 <= arr[i], mat[r][c] <= m * n
// · All the integers of arr are unique.
// · All the integers of mat are unique.

int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matmax_colsize) {
    int max_rows = matSize;
    int max_cols = *matmax_colsize;

    int row[arrSize];                                                                                       
    int col[arrSize];                                                                                       
    
    int n_row[max_rows];        
    int n_col[max_cols];

    memset(n_row, 0, sizeof(n_row));
    memset(n_col, 0, sizeof(n_col));
    
    for (int i = 0; i < max_rows; i++) {
        for (int j = 0; j < max_cols; j++) {
            int valor = mat[i][j];        
            row[valor - 1] = i;                                                                             //stores the row of a value for O(1) access
            col[valor - 1] = j;                                                                             //stores the column of a value for O(1) access
        }
    }

    for (int i = 0; i < arrSize; i++) {                                                                     //iterate through the array of painting order
        int valor = arr[i];                                                                                 
        if (++n_row[row[valor - 1]] == max_cols || ++n_col[col[valor - 1]] == max_rows) return i;           //if a column or row is completed return the number of steps
    }

    return 0;
}

// Runtime: 3ms 
// Memory: 22.60MB