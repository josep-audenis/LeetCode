# A sequence x1, x2, ..., xn is Fibonacci-like if:
# · n >= 3
# · xi + xi+1 == xi+2 for all i + 2 <= n

# Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.

# A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].

# - Example 1:
# Input: arr = [1,2,3,4,5,6,7,8]
# Output: 5
# Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].

# - Example 2:
# Input: arr = [1,3,7,11,12,14,18]
# Output: 3
# Explanation: The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].

# Constraints:
# · 3 <= arr.length <= 1000
# · 1 <= arr[i] < arr[i + 1] <= 10^9

class Solution:
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        n = len(arr)  # Get the length of the input array
        max_len = 0  # Variable to track the maximum length of Fibonacci-like subsequence
        lengths = [[0] * n for i in range(n)]  # 2D array to store lengths of subsequences

        v_idx = {num: idx for idx, num in enumerate(arr)}  # Dictionary to map each value to its index

        for current in range(n):  # Iterate over the current element
            for prev in range(current):  # Iterate over the previous elements
                diff = arr[current] - arr[prev]  # Calculate the difference between current and previous element
                prev_idx = v_idx.get(diff, -1)  # Get index of the element equal to the difference if exists

                if diff < arr[prev] and prev_idx >= 0:  # Valid Fibonacci condition (diff must be smaller and exist in array)
                    lengths[prev][current] = lengths[prev_idx][prev] + 1  # Extend the length of the subsequence
                else:
                    lengths[prev][current] = 2  # Initialize a new subsequence of length 2

                max_len = max(max_len, lengths[prev][current])  # Update the maximum length found

        if max_len > 2:  # If the maximum length is greater than 2, return it
            return max_len
        else:  # Otherwise, return 0 (no valid subsequence found)
            return 0


# Time Complexity: O(n^2)
# Space Complexity: O(n^2)