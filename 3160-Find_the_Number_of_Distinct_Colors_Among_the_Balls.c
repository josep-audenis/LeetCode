// You are given an integer limit and a 2D array queries of size n x 2.
// There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color y. After each query, you need to find the number of distinct colors among the balls.
// 
// Return an array result of length n, where result[i] denotes the number of distinct colors after ith query.
// 
// Note that when answering a query, lack of a color will not be considered as a color.
// 
// - Example 1:
// Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
// Output: [1,2,2,3]
// Explanation:
// After query 0, ball 1 has color 4.
// After query 1, ball 1 has color 4, and ball 2 has color 5.
// After query 2, ball 1 has color 3, and ball 2 has color 5.
// After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.
// 
// - Example 2:
// Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
// Output: [1,2,2,3,4]
// Explanation:
// After query 0, ball 0 has color 1.
// After query 1, ball 0 has color 1, and ball 1 has color 2.
// After query 2, ball 0 has color 1, and balls 1 and 2 have color 2.
// After query 3, ball 0 has color 1, balls 1 and 2 have color 2, and ball 3 has color 4.
// After query 4, ball 0 has color 1, balls 1 and 2 have color 2, ball 3 has color 4, and ball 4 has color 5.
//  
// Constraints:
// · 1 <= limit <= 109
// · 1 <= n == queries.length <= 105
// · queries[i].length == 2
// · 0 <= queries[i][0] <= limit

typedef struct {
    int key;                                                            //key of the hash table entry
    int value;                                                          //value associated with the key
    UT_hash_handle hh;                                                  //internal handle for uthash functionality
} HashMap;

void insert(HashMap** map, int key, int value) {
    HashMap* entry;
    HASH_FIND_INT(*map, &key, entry);                                   //search for the key in the hash table

    if (entry) {
        entry->value = value;                                           //if found, update the value
    } else {                                                            //if not found, create a new entry in the hash table
        entry = (HashMap*)malloc(sizeof(HashMap));
        entry->key = key;
        entry->value = value;
        HASH_ADD_INT(*map, key, entry);                                 //add the new entry to the hash table
    }
}

int get(HashMap* map, int key, int defaultValue) {
    HashMap* entry;
    HASH_FIND_INT(map, &key, entry);                                    //search for the key in the hash table

    return (entry ? entry->value : defaultValue);                       //return the value or the default
}

void erase(HashMap** map, int key) {
    HashMap* entry;
    HASH_FIND_INT(*map, &key, entry);                                   //search for the key in the hash table

    if (entry) {
        HASH_DEL(*map, entry);                                          //remove the entry from the hash table
        free(entry);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* queryResults(int limit, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* result = malloc(queriesSize * sizeof(int));  
    HashMap* ballColor = NULL;                                          //hash map to store the color of each ball
    HashMap* colorCount = NULL;                                         //hash map to count how many balls have each color

    for (int i = 0; i < queriesSize; i++) {
        int ball = queries[i][0], color = queries[i][1];                //extract ball and color from query
        int oldColor = get(ballColor, ball, -1);                        //get the current color of the ball (if any)

        
        if (oldColor != -1) {                                           //if the ball already had a color assigned, update the count for that color
            int count = get(colorCount, oldColor, 0) - 1;               //decrease count of balls with that color
            if (count == 0) {
                erase(&colorCount, oldColor);                           //if no balls remain with that color, remove it
            } else {
                insert(&colorCount, oldColor, count);                   //otherwise, update the count
            }
        }

        insert(&ballColor, ball, color);                            
        insert(&colorCount, color, get(colorCount, color, 0) + 1);      //assign the new color to the ball and update the color count

        int distinctColors = HASH_COUNT(colorCount);                    //count how many distinct colors are currently in use
        result[i] = distinctColors;                                     
    }

    *returnSize = queriesSize;  

    return result;  
}

// Runtime: 163ms 
// Memory: 119.44MB