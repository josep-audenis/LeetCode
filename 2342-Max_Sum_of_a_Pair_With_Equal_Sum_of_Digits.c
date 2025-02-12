// You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].
// 
// Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions.
// 
// - Example 1:
// Input: nums = [18,43,36,13,7]
// Output: 54
// Explanation: The pairs (i, j) that satisfy the conditions are:
// - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
// - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
// So the maximum sum that we can obtain is 54.
// 
// - Example 2:
// Input: nums = [10,12,19,14]
// Output: -1
// Explanation: There are no two numbers that satisfy the conditions, so we return -1.
//  
// Constraints:
// · 1 <= nums.length <= 105
// · 1 <= nums[i] <= 109

uint16_t sum(int val) {
    uint16_t sum = 0;
    
    while(val != 0) {								// Iterate through all the numbers in the integer
        sum += val % 10;				
        val /= 10;
    }

    return sum;
}

uint32_t max(int v1, int v2) {			
    return (v1 > v2 ? v1 : v2);						// Returns the max value of two given integers
}

int maximumSum(int* nums, int numsSize) {
    uint32_t * map = calloc(90, sizeof(uint32_t));
    int res = -1;

    for (int i = 0; i < numsSize; i++) {
        uint16_t val = sum(nums[i]);
        
        if (map[val] != 0) {						// If there's no value equal to the sum of the digits
            res = max(res, map[val] + nums[i]);		// Stores the max value of the sum
        }
        map[val] = max(map[val], nums[i]);			// Stores the new value if it's greater than the previous one
    }

    free(map);
    return res;
}

// Runtime: 4ms 
// Memory: 15.74MB