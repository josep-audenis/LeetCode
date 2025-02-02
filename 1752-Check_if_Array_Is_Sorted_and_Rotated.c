// Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.
// 
// There may be duplicates in the original array.
// 
// Note: An array A rotated by x positions results in an array B of the same length such that A[i] == B[(i+x) % A.length], where % is the modulo operation.
// 
// - Example 1:
// Input: nums = [3,4,5,1,2]
// Output: true
// Explanation: [1,2,3,4,5] is the original sorted array.
// You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].
// 
// - Example 2:
// Input: nums = [2,1,3,4]
// Output: false
// Explanation: There is no sorted array once rotated that can make nums.
// 
// - Example 3:
// Input: nums = [1,2,3]
// Output: true
// Explanation: [1,2,3] is the original sorted array.
// You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
//  
// Constraints:
// · 1 <= nums.length <= 100
// · 1 <= nums[i] <= 100

bool check(int* nums, int numsSize) {
    
    uint8_t dis = 0;                                                        //number of disordered occurrences

    for (uint8_t i = 0; i < (numsSize - 1); i++) {
        if (nums[i] > nums[i+1] && ++dis > 1) return false;                 //if more than one disorder means the array was never sorted
    }
    if (nums[numsSize-1] > nums[0] && ++dis > 1) return false;              //check for the first and last positions

    return true;                                                            //if one or none disorders found the array is either sorted or rotated
}

// Runtime: 0ms 
// Memory: 8MB