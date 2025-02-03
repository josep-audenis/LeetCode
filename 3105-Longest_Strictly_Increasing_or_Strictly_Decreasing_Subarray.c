// You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
// 
// - Example 1:
// Input: nums = [1,4,3,3,2]
// Output: 2
// Explanation:
// The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
// The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
// Hence, we return 2.
// 
// - Example 2:
// Input: nums = [3,3,3,3]
// Output: 1
// Explanation:
// The strictly increasing subarrays of nums are [3], [3], [3], and [3].
// The strictly decreasing subarrays of nums are [3], [3], [3], and [3].
// Hence, we return 1.
// 
// - Example 3:
// Input: nums = [3,2,1]
// Output: 3
// Explanation:
// The strictly increasing subarrays of nums are [3], [2], and [1].
// The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1], and [3,2,1].
// Hence, we return 3.
// 
// Constraints:
// · 1 <= nums.length <= 50
// · 1 <= nums[i] <= 50

int max(int v1, int v2) {
    return (v1 > v2 ? v1 : v2);                                     //return max value from two integer
}

int longestMonotonicSubarray(int* nums, int numsSize) {
    
    int res = 1, inc = 1, dec = 1;                                  

    for (int i = 1; i < numsSize; i++) {                            //iterate one time the array
        if (nums[i-1] < nums[i]) {                                  //if increasing, increment the increment counter and reset the decrement
            inc++;
            dec = 1;
        } else if (nums[i-1] > nums[i]) {                           //if decrementing, increment the decrement counter and reset the decrement
            inc = 1;
            dec++;
        } else {                                                    //otherwise means values are equal hence reseting both counters
            inc = dec = 1;
        }
        res = max(max(dec, inc), res);                              //get the maximum value between both counters and the current maximum length
    }

    return res;                                                     //return max length
}

// Runtime: 0ms 
// Memory: 8.86MB