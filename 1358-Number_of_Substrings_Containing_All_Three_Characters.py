# Given a string s consisting only of characters a, b and c.

# Return the number of substrings containing at least one occurrence of all these characters a, b and c.

# - Example 1:
# Input: s = "abcabc"
# Output: 10
# Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

# - Example 2:
# Input: s = "aaacb"
# Output: 3
# Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

# - Example 3:
# Input: s = "abc"
# Output: 1
 
# Constraints:
# · 3 <= s.length <= 5 x 10^4
# · s only consists of a, b or c characters.

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        start = end = count = 0
        letters = [0] * 3

        while end < len(s):
            letters[ord(s[end]) - ord("a")] += 1

            while letters[0] > 0 and letters[1] > 0 and letters[2] > 0:
                count += len(s) - end

                letters[ord(s[start]) - ord("a")] -= 1
                start += 1

            end += 1

        return count

# Time Complexity: O()
# Space Complexity: O()