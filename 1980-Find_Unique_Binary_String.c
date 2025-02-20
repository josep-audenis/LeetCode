// Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

// - Example 1:
// Input: nums = ["01","10"]
// Output: "11"
// Explanation: "11" does not appear in nums. "00" would also be correct.

// - Example 2:
// Input: nums = ["00","01"]
// Output: "11"
// Explanation: "11" does not appear in nums. "10" would also be correct.

// - Example 3:
// Input: nums = ["111","011","001"]
// Output: "101"
// Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
 
// Constraints:
// · n == nums.length
// · 1 <= n <= 16
// · nums[i].length == n
// · nums[i] is either '0' or '1'.
// · All the strings of nums are unique.

char* findDifferentBinaryString(char** nums, int numsSize) {	// Tis approach follows the mathematical theory of Cantor's Diagonal Argument
    char * string = malloc(sizeof(char) * (numsSize + 1)); 		// Allocate memory for the result string

    for (uint8_t i = 0; i < numsSize; i++) {					
        string[i] = (nums[i][i] == '1' ? '0' : '1');			// Flip the ith character of the ith string
    }

    string[numsSize] = '\0';
    return string;
}

// Time Complexity: O(n)
// Space Complexity: O(1)