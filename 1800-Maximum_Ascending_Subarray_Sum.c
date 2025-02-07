// Given an array of positive integers nums, return the maximum possible sum of an ascending subarray in nums.
// 
// A subarray is defined as a contiguous sequence of numbers in an array.
// 
// A subarray [numsl, numsl+1, ..., numsr-1, numsr] is ascending if for all i where l <= i < r, numsi  < numsi+1. Note that a subarray of size 1 is ascending.
// 
// - Example 1:
// Input: nums = [10,20,30,5,10,50]
// Output: 65
// Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
// 
// - Example 2:
// Input: nums = [10,20,30,40,50]
// Output: 150
// Explanation: [10,20,30,40,50] is the ascending subarray with the maximum sum of 150.
// 
// - Example 3:
// Input: nums = [12,17,15,13,10,11,12]
// Output: 33
// Explanation: [10,11,12] is the ascending subarray with the maximum sum of 33.
//  
// - Constraints:
// 1 <= nums.length <= 100
// 1 <= nums[i] <= 100

int max(uint16_t v1, uint16_t v2) {
    return (v1 > v2 ? v1 : v2);							//return the max value of two integers
}

int maxAscendingSum(int* nums, int numsSize) {

    uint16_t inc = nums[0], res = 0;					//set the initial value of the array to the sum
    
    for (uint8_t i = 1; i < numsSize; i++) {
        if (nums[i-1] < nums[i]) {
            inc += nums[i];								//if the array is increasing we add the new value to the increment sum
        } else {
            res = max(inc, res);						//otherwise we check if the current addition is the current highest and set it if so
            inc = nums[i];								//set the current value of the array to be the first value of the addition
        }
    }
    
    return max(inc, res);								//return the maximum value between the current highest sum or the current increasing addition
}

// Runtime: 0ms 
// Memory: 8.12MB