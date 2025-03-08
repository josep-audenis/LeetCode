// You are given a 0-indexed string blocks of length n, where blocks[i] is either 'W' or 'B', representing the color of the ith block. The characters 'W' and 'B' denote the colors white and black, respectively.

// You are also given an integer k, which is the desired number of consecutive black blocks.

// In one operation, you can recolor a white block such that it becomes a black block.

// Return the minimum number of operations needed such that there is at least one occurrence of k consecutive black blocks.

// - Example 1:
// Input: blocks = "WBBWWBBWBW", k = 7
// Output: 3
// Explanation:
// One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
// so that blocks = "BBBBBBBWBW". 
// It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
// Therefore, we return 3.

// - Example 2:
// Input: blocks = "WBWBBBW", k = 2
// Output: 0
// Explanation:
// No changes need to be made, since 2 consecutive black blocks already exist.
// Therefore, we return 0.
 
// Constraints:
// · n == blocks.length
// · 1 <= n <= 100
// · blocks[i] is either 'W' or 'B'.
// · 1 <= k <= n

uint8_t min(uint8_t * a, uint8_t * b) {
    return (*a < *b ? *a : *b);
}

int minimumRecolors(char* blocks, int k) {
    uint8_t l = 0, white = 0;
    uint8_t color = k;

    for (uint8_t r = 0; blocks[r] != '\0'; r++) {
        if (blocks[r] == 'W') {
            white += 1;
        }

        if (r - l + 1 == k) {
            color = min(&color, &white);

            if (blocks[l] == 'W') {
                white -= 1;
            }

            l += 1;
        }
    }

    return color;
}

// Time Complexity: O(n)
// Space Complexity: O(1)