// Given an integer n, find a sequence that satisfies all of the following:
// · The integer 1 occurs once in the sequence.
// · Each integer between 2 and n occurs twice in the sequence.
// · For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
// 
// The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
// 
// Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.
// 
// A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
// 
// - Example 1:
// Input: n = 3
// Output: [3,1,2,3,2]
// Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
// 
// - Example 2:
// Input: n = 5
// Output: [5,3,1,4,3,5,2,4,2]
//  
// Constraints:
// · 1 <= n <= 20

bool lexicoSequence(int index, int *res, bool *used, uint8_t target) {

    if (index == (target * 2 - 1)) {											
        return true;															// If we have filled all positions, return true.
    }

    if (res[index] != 0) {												    	
        return lexicoSequence(index + 1, res, used, target);					// If the current position is already filled, move to the next index.
    }

    for (int i = target; i >= 1; i--) {											// Try placing numbers from target down to 1 (ensuring lexicographically largest order).
        if (used[i]) {
			continue; 															// Skip numbers that are already used.
		}

        used[i] = true;   														// Mark the number as used.
        res[index] = i;   														// Place the number at the current index.

        if (i == 1) {  															// Special case for `1`, which appears only once.
            if (lexicoSequence(index + 1, res, used, target)) {
                return true;
            }
        } else if ((index + i) < (target * 2 - 1) && res[index + i] == 0) {		// For numbers > 1, check if we can place the second occurrence at (index + i).
            res[index + i] = i;  												// Place the second occurrence.

            if (lexicoSequence(index + 1, res, used, target)) {					// Recursively attempt to fill the rest of the sequence.
                return true;
            }

            res[index + i] = 0; 												// Backtrack if unsuccessful.
        }

        res[index] = 0;   														// Reset the current position for backtracking.
        used[i] = false;  														
    }

    return false;  																// No valid sequence found.
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructDistancedSequence(int n, int* returnSize) {
    *returnSize = n * 2 - 1;  													// The sequence length.

    int *res = calloc(*returnSize, sizeof(int));  								// Initialize the sequence with zeros.
    bool *used = calloc(n + 1, sizeof(bool));     								// Boolean array to track used numbers.

    lexicoSequence(0, res, used, n);  											// Start recursive sequence construction.

    free(used);  																

    return res;  																
}

// Runtime: 0ms 
// Memory: 8.15MB