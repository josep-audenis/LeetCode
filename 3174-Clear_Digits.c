// You are given a string s.
// Your task is to remove all digits by doing this operation repeatedly:
// 
// Delete the first digit and the closest non-digit character to its left.
// Return the resulting string after removing all digits.
// 
// -Example 1:
// Input: s = "abc"
// Output: "abc"
// Explanation:
// There is no digit in the string.
// 
// - Example 2:
// Input: s = "cb34"
// Output: ""
// Explanation:
// First, we apply the operation on s[2], and s becomes "c4".
// Then we apply the operation on s[1], and s becomes "".
//  
// Constraints:
// · 1 <= s.length <= 100
// · s consists only of lowercase English letters and digits.
// · The input is generated such that it is possible to delete all digits.


bool isDigit(char digit) {
    return (digit >= '0' && digit <= '9');				// Ceck if the character is a digit
}

int max(int v1, int v2) {
    return (v1 > v2 ? v1 : v2);							// Return the maximum value between 2 integers
}

char* clearDigits(char* s) {
    uint8_t index = 0;

    for (uint8_t i = 0; i < strlen(s); i++) {			// Iterate through all the string
        if (isDigit(s[i])) {							// If the character is a digit, substract one from the result index
            index = max(index - 1, 0);
        } else {
            s[index++] = s[i];							// If the character is not a digit, overwrite the value of the current index with the result index & increment result index
        }
    }

    s = realloc(s, sizeof(char) * (index+1));			// Realloc the size of the string
    s[index] = '\0';

    return s;
}

// Runtime: 0ms 
// Memory: 7.83MB