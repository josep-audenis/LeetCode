// A happy string is a string that:
// · consists only of letters of the set ['a', 'b', 'c'].
// · s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
// 
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
// 
// Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
// 
// Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
// 
// - Example 1:
// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
// 
// - Example 2:
// Input: n = 1, k = 4
// Output: ""
// Explanation: There are only 3 happy strings of length 1.
// 
// - Example 3:
// Input: n = 3, k = 9
// Output: "cab"
// Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
//  
// Constraints:
// · 1 <= n <= 10
// · 1 <= k <= 100

char* getHappyString(int n, int k) {
    
    uint16_t total = 3 * (1 << (n - 1));						// Calculate with variations with repetitions the total amount of combinations 3*2^(n-1) = 3^n
    uint16_t index = k - 1;									// k is given as 1-indexed
    uint16_t groupSize = total / 3;							// Size of each group starting with 'a', 'b', or 'c'
    
    if (k > total) {									// If k is greater than the total number of happy strings, return an empty string
        return "";
    }

    char* result = malloc(sizeof(char) * (n + 1));

    result[0] = 'a' + (index / groupSize); 				// Determine the first character ('a', 'b', or 'c')
    index %= groupSize;							

    for (uint8_t i = 1; i < n; i++) {
        groupSize /= 2; 								// Each subsequent character halves the group size
        switch(result[i - 1]) {							// Choose the next character that is different from the previous one
            case 'a':
                result[i] = (index < groupSize) ? 'b' : 'c';
                break;
            case 'b':
                result[i] = (index < groupSize) ? 'a' : 'c';
                break;
            case 'c':
                result[i] = (index < groupSize) ? 'a' : 'b';
                break;
        }
        index %= groupSize;
    }

    result[n] = '\0';

    return result;
}

// Time Complexity: O(log(n))
// Space Complexity: O(n)