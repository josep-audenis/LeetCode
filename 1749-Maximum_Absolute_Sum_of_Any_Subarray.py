# You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

# Return the maximum absolute sum of any (possibly empty) subarray of nums.

# Note that abs(x) is defined as follows:
# · If x is a negative integer, then abs(x) = -x.
# · If x is a non-negative integer, then abs(x) = x.
 
# - Example 1:
# Input: nums = [1,-3,2,3,-4]
# Output: 5
# Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

# - Example 2:
# Input: nums = [2,-5,1,-4,3,-2]
# Output: 8
# Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.
 

# Constraints:
# · 1 <= nums.length <= 10^5
# · -104 <= nums[i] <= 10^4

class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        current_max = 0
        current_min = 0
        max_val = 0
        min_val = 0

        for i in nums:
            current_max = max(i, current_max+i)	# Get max value between the current number and the current acumulation
            max_val = max(current_max, max_val)	# Get max value between current count and max value
            current_min = min(i, current_min+i)	# Get min value between the current number and the current acumulation
            min_val = min(current_min, min_val)	# Get min value between current count and min value

        return max(abs(max_val), abs(min_val))	# Return the biggest between the max value of the positive and negative counts

# Time Complexity: O(n)
# Space Complexity: O(1)
