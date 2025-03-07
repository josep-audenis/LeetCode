# Given two positive integers left and right, find the two integers num1 and num2 such that:
# · left <= num1 < num2 <= right .
# · Both num1 and num2 are prime numbers.
# · num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.

# Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

# - Example 1:
# Input: left = 10, right = 19
# Output: [11,13]
# Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
# The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
# Since 11 is smaller than 17, we return the first pair.

# - Example 2:
# Input: left = 4, right = 6
# Output: [-1,-1]
# Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.
 
# Constraints:
# · 1 <= left <= right <= 10^6

class Solution:
    def sieve(self, n):
        prime = [True for i in range(n+1)]
        p = 2
        while (p * p <= n):

            if (prime[p] == True):	# If prime[p] is not changed, then it is a prime

                for i in range(p * p, n+1, p):	# Update all multiples of p
                    prime[i] = False
            p += 1

        prime[0] = prime[1] = False	# 0 and 1 are not primes
        return prime

    def closestPrimes(self, left: int, right: int) -> List[int]:
        res = [-1, -1]
        sieve = self.sieve(right)

        primes = [num for num in range(left, right + 1) if sieve[num]]

        if len(primes) < 2:	# We need more at least 2 primes
            return res

        min_diff = float("inf")

        for i in range(1, len(primes)):
            diff = primes[i] - primes[i - 1]
            if diff < min_diff:	# Get minimum distance between current primes and current minimum distance
                min_diff = diff
                res = [primes[i - 1], primes[i]]	# Update result

        return res

# Time Complexity: O(nlog(log(n)))
# Space Complexity: O(n)