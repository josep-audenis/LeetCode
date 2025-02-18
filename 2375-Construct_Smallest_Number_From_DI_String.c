// You are given a 0-indexed string pattern of length n consisting of the characters 'I' meaning increasing and 'D' meaning decreasing.
// 
// A 0-indexed string num of length n + 1 is created using the following conditions:
// · num consists of the digits '1' to '9', where each digit is used at most once.
// · If pattern[i] == 'I', then num[i] < num[i + 1].
// · If pattern[i] == 'D', then num[i] > num[i + 1].
// 
// Return the lexicographically smallest possible string num that meets the conditions.
// 
// - Example 1:
// Input: pattern = "IIIDIDDD"
// Output: "123549876"
// Explanation:
// At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
// At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
// Some possible values of num are "245639871", "135749862", and "123849765".
// It can be proven that "123549876" is the smallest possible num that meets the conditions.
// Note that "123414321" is not possible because the digit '1' is used more than once.
// 
// - Example 2:
// Input: pattern = "DDD"
// Output: "4321"
// Explanation:
// Some possible values of num are "9876", "7321", and "8742".
// It can be proven that "4321" is the smallest possible num that meets the conditions.
// 
// Constraints:
// · 1 <= pattern.length <= 8
// · pattern consists of only the letters 'I' and 'D'.

char* smallestNumber(char* pattern) {
    
    int8_t top = -1, index = 0, length = strlen(pattern);
    char * res = malloc(length + 2);
    uint8_t stack[length + 1];

    for (uint8_t i = 0; i <= length; i++) {				// Iterate through the pattern and build the number
        stack[++top] = i+1;								// Push the next number onto the stack
    
        if (i == length | pattern[i] == 'I') {			// When we encounter 'I' or reach the end, pop all elements from the stack
            while(top >= 0) {
                res[index++] = stack[top--] + '0';		// Append the number to the result
            }
        }
    }

    res[index] = '\0';									// Add null terminator to make it a valid string
    return res;
}

// Time Complexity: O(n)
// Space Complexity: O(n)