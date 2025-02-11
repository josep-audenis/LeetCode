// Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:
// 
// Find the leftmost occurrence of the substring part and remove it from s.
// Return s after removing all occurrences of part.
// 
// A substring is a contiguous sequence of characters in a string.
// 
// - Example 1:
// Input: s = "daabcbaabcbc", part = "abc"
// Output: "dab"
// Explanation: The following operations are done:
// - s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
// - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
// - s = "dababc", remove "abc" starting at index 3, so s = "dab".
// Now s has no occurrences of "abc".
// 
// - Example 2:
// Input: s = "axxxxyyyyb", part = "xy"
// Output: "ab"
// Explanation: The following operations are done:
// - s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
// - s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
// - s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
// - s = "axyb", remove "xy" starting at index 1 so s = "ab".
// Now s has no occurrences of "xy".
// 
// Constraints:
// 1 <= s.length <= 1000
// 1 <= part.length <= 1000
// s​​​​​​ and part consists of lowercase English letters.

char* removeOccurrences(char* s, char* part) {
    uint16_t index = 0;
    uint16_t len1 = strlen(s), len2 = strlen(part);
    char *res = malloc(len1 + 1);
    
    for (int i = 0; i < len1; i++) {                                // Iterate through all the string
        
        res[index++] = s[i];
        uint16_t count = 0;
        if (index >= len2) {                                        // Avoid problems with lower indexes

            for (int j = 0; j < len2; j++) {                        // Iterate through all the part string
                if (res[index - len2 + j] == part[j]) count++;      // Increment the amount of equal characters
            }

            if (count == len2) index -= len2;                       // If found the entire part, substract the part length from the result index
        }
    }
    
    res = realloc(res, sizeof(char) * (index + 1));
    res[index] = '\0';

    return res;
}

// Runtime: 4ms 
// Memory: 8.19MB