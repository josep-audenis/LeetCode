# Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.

# An integer y is a power of three if there exists an integer x such that y == 3^x.

# - Example 1:
# Input: n = 12
# Output: true
# Explanation: 12 = 31 + 32

# - Example 2:
# Input: n = 91
# Output: true
# Explanation: 91 = 30 + 32 + 34

# - Example 3:
# Input: n = 21
# Output: false
 
# Constraints:
# 1 <= n <= 10^7

class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        while n > 0:
            if n % 3 == 2:	# If the module is 2 the exponent is repeated and thus not valid
                return False
            n //= 3	# Floor by 3 to get the quotient
        return True

# Time Complexity: O(n)
# Space Complexity: O(1)