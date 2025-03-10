# You are given a string word and a non-negative integer k.

# Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.

# - Example 1:
# Input: word = "aeioqq", k = 1
# Output: 0
# Explanation:
# There is no substring with every vowel.

# - Example 2:
# Input: word = "aeiou", k = 0
# Output: 1
# Explanation:
# The only substring with every vowel and zero consonants is word[0..4], which is "aeiou".

# - Example 3:
# Input: word = "ieaouqqieaouqq", k = 1
# Output: 3
# Explanation:
# The substrings with every vowel and one consonant are:
# · word[0..5], which is "ieaouq".
# · word[6..11], which is "qieaou".
# · word[7..12], which is "ieaouq".

# Constraints:
# · 5 <= word.length <= 2 * 10^5
# · word consists only of lowercase English letters.
# · 0 <= k <= word.length - 5

class Solution:
    def isVowel(self, char :str) -> bool:
        return char == 'a' or char == 'e' or char == 'i' or char == 'o' or char == 'u'
    
    def countOfSubstrings(self, word: str, k: int) -> int:
        count = 0
        start = end = 0
        
        vowels = {}
        constants = 0
        next_index = len(word)
        next_const = [0] * next_index

        for i in range(len(word) - 1, -1 , -1):
            next_const[i] = next_index
            if not self.isVowel(word[i]):
                next_index = i

        while end < len(word):
            new = word[end]
            if self.isVowel(new):
                vowels[new] = vowels.get(new, 0) + 1
            else:
                constants += 1

            while constants > k:
                letter = word[start]
                if self.isVowel(letter):
                    vowels[letter] -= 1
                    if vowels[letter] == 0:
                        del vowels[letter]
                else:
                    constants -= 1
                start += 1

            while start < len(word) and len(vowels) == 5 and constants == k:
                count += next_const[end] - end
                letter = word[start]
                if self.isVowel(letter):
                    vowels[letter] -= 1
                    if vowels[letter] == 0:
                        del vowels[letter]
                else:
                    constants -= 1
                start += 1

            end += 1
        
        return count

# Time Complexity: O(n)
# Space Complexity: O(n)