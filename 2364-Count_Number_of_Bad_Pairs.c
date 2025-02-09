// You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].
// 
// Return the total number of bad pairs in nums.
// 
// - Example 1:
// Input: nums = [4,1,3,3]
// Output: 5
// Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
// The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
// The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
// The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
// The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
// There are a total of 5 bad pairs, so we return 5.
// 
// - Example 2:
// Input: nums = [1,2,3,4,5]
// Output: 0
// Explanation: There are no bad pairs.
//  
// Constraints:
// · 1 <= nums.length <= 105
// · 1 <= nums[i] <= 109

typedef struct {
    int key;                                        // Difference value (i - nums[i])
    int count;                                      // Number of occurrences of this difference
    UT_hash_handle hh;                              // Handle for uthash
} HashEntry;

long countBadPairs(int* nums, int numsSize) {
    long badPairs = 0;
    HashEntry *diffCount = NULL, *entry;

    for (int pos = 0; pos < numsSize; pos++) {      // Iterate through the array
        int diff = pos - nums[pos];                 // Calculate the difference
    
        HASH_FIND_INT(diffCount, &diff, entry);     // Check if the difference is already in the hash table
        
        int goodPairsCount = (entry != NULL) ? entry->count : 0;     // If found, get the count of good pairs
        
        badPairs += pos - goodPairsCount;           // Total possible pairs at this position minus good pairs = bad pairs
        
        if (entry) {                                // Update the count in the hash table
            entry->count++;
        } else {
            entry = malloc(sizeof(HashEntry));      
            entry->key = diff;
            entry->count = 1;
            HASH_ADD_INT(diffCount, key, entry);
        }
    }

    HashEntry *current, *tmp;                   
    HASH_ITER(hh, diffCount, current, tmp) {        // Free the hash table
        HASH_DEL(diffCount, current);
        free(current);
    }

    return badPairs;
}

// Runtime: 105ms 
// Memory: 54.1MB   