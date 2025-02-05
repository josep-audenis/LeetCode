// You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
// 
// Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
// 
// - Example 1:
// Input: s1 = "bank", s2 = "kanb"
// Output: true
// Explanation: For example, swap the first character with the last character of s2 to make "bank".
// 
// - Example 2:
// Input: s1 = "attack", s2 = "defend"
// Output: false
// Explanation: It is impossible to make them equal with one string swap.
// 
// - Example 3:
// Input: s1 = "kelb", s2 = "kelb"
// Output: true
// Explanation: The two strings are already equal, so no string swap operation is required.
//  
// Constraints:
// · 1 <= s1.length, s2.length <= 100
// · s1.length == s2.length
// · s1 and s2 consist of only lowercase English letters.

bool areAlmostEqual(char* s1, char* s2) {
    
    int8_t index = -1;

    for (uint8_t i = 0; i < strlen(s1); i++) {
        if (s1[i] == s2[i]) continue;
        if (index < 0) {												//if not found an initial swaping index 
            if (index == -2) return false;								//if there's already one swap return false
            if (index == -1) index = i;									//if first swap, store the index
            continue;
        } else {
            if (s2[i] == s1[index] && s1[i] == s2[index]) index = -2;	//if the values are correctly swapped set the index to done
            else return false;											//if the swapping values are not correct return false
        }
    }
    return (index < 0 ? true : false);									//only return true if there are no swappings or only one complete swapping
}

// Runtime: 0ms 
// Memory: 7.78MB