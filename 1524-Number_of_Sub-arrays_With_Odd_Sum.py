# Given an array of integers arr, return the number of subarrays with an odd sum.

# Since the answer can be very large, return it modulo 10^9 + 7.

# - Example 1:
# Input: arr = [1,3,5]
# Output: 4
# Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
# All sub-arrays sum are [1,4,9,3,8,5].
# Odd sums are [1,9,3,5] so the answer is 4.

# - Example 2:
# Input: arr = [2,4,6]
# Output: 0
# Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
# All sub-arrays sum are [2,6,12,4,10,6].
# All sub-arrays have even sum and the answer is 0.

# - Example 3:
# Input: arr = [1,2,3,4,5,6,7]
# Output: 16
 
# Constraints:
# · 1 <= arr.length <= 10^5
# · 1 <= arr[i] <= 100

class Solution:
    def numOfSubarrays(self, arr: List[int]) -> int:
        odd = 0	# Counter of sets that are odd 
        even = 0	# Counter of sets that are even
        count = 0
        
        for i in arr:
            if i % 2 != 0:	# Check if number is odd
                odd, even = even, odd # Swap the values of odd and even counters since: o + o = e & e + e = e & o + e = o 
                odd += 1	# Increment the odd counter
            else:	
                even += 1	# Increment the even counter
            count += odd	# Add the current value of the odd counter to the total count of sets

        return count % 1000000007

# Time Complexity: O(n)
# Space Comlexity: O(1)