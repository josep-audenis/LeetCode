// You have n  tiles, where each tile has one letter tiles[i] printed on it.
// 
// Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.
// 
// - Example 1:
// Input: tiles = "AAB"
// Output: 8
// Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
// 
// - Example 2:
// Input: tiles = "AAABBC"
// Output: 188
// 
// - Example 3:
// Input: tiles = "V"
// Output: 1
//  
// Constraints:
// · 1 <= tiles.length <= 7
// · tiles consists of uppercase English letters.

int combine(uint8_t * count) {
    int total = 0;
    
    for (uint8_t i = 0; i < 26; i++) {	    							// Iterate over the 26 possible letters (A-Z)
        if (count[i] == 0) {											// Skip if no more of this letter are available
            continue;								
        }
        
        total++;														// Count the current sequence
        count[i]--;														// Reduce the frequency of the current letter
        total += combine(count);										// Recursive call with the updated counts
        count[i]++;														// Restore the letter count before moving to the next
    }
    
    return total;
}


int numTilePossibilities(char* tiles) {
    uint8_t * count = calloc(sizeof(uint8_t), sizeof(uint8_t) * 26);
    
    for (int i = 0; tiles[i] != '\0'; i++) {							
        count[tiles[i] - 'A']++;										// Convert character to index and increase its count
    }
    
    return combine(count);												// Call the recursive function
 
}

// Runtime: 3ms 
// Memory: 7.68MB