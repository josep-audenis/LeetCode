// Design a number container system that can do the following:
// · Insert or Replace a number at the given index in the system.
// · Return the smallest index for the given number in the system.
// 
// Implement the NumberContainers class:
// · NumberContainers() Initializes the number container system.
// · void change(int index, int number) Fills the container at index with the number. If there is already a number at that index, replace it.
// · int find(int number) Returns the smallest index for the given number, or -1 if there is no index that is filled by number in the system.
//  
// Example 1:
// Input
// ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
// [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
// Output
// [null, -1, null, null, null, null, 1, null, 2]
// Explanation
// NumberContainers nc = new NumberContainers();
// nc.find(10); // There is no index that is filled with number 10. Therefore, we return -1.
// nc.change(2, 10); // Your container at index 2 will be filled with number 10.
// nc.change(1, 10); // Your container at index 1 will be filled with number 10.
// nc.change(3, 10); // Your container at index 3 will be filled with number 10.
// nc.change(5, 10); // Your container at index 5 will be filled with number 10.
// nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the smallest index that is filled with 10 is 1, we return 1.
// nc.change(1, 20); // Your container at index 1 will be filled with number 20. Note that index 1 was filled with 10 and then replaced with 20. 
// nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest index that is filled with 10 is 2. Therefore, we return 2.
// 
// Constraints:
// · 1 <= index, number <= 109
// · At most 105 calls will be made in total to change and find.

// Structure to map an index to a number
typedef struct {
    int index;  // Index value
    int number; // Associated number
    UT_hash_handle hh; // Hash handle for uthash
} IndexToNumber;

// Structure to map a number to a set of indices
typedef struct {
    int number;     // The number itself
    int *indices;   // Dynamic array of indices
    int size;       // Current number of indices
    int capacity;   // Capacity of the indices array
    UT_hash_handle hh; // Hash handle for uthash
} NumberToIndices;

// Main structure to hold mappings
typedef struct {
    IndexToNumber * indexToNumbers;  // Hash table mapping index -> number
    NumberToIndices * numberToIndices; // Hash table mapping number -> indices
} NumberContainers;

// Function to create a new NumberContainers instance
NumberContainers * numberContainersCreate() {
    NumberContainers * obj = malloc(sizeof(NumberContainers));
    obj->indexToNumbers = NULL;
    obj->numberToIndices = NULL;
    return obj;
}

// Function to update or add an index-number mapping
void numberContainersChange(NumberContainers * obj, int index, int number) {
    IndexToNumber * entry;
    HASH_FIND_INT(obj->indexToNumbers, &index, entry);
    
    if (entry) {
        int prevNumber = entry->number;
        if (prevNumber == number) return; // No change needed if the number is the same
        
        // Remove index from the old number's mapping
        NumberToIndices * numEntry;
        HASH_FIND_INT(obj->numberToIndices, &prevNumber, numEntry);

        if (numEntry) {
            for (int i = 0; i < numEntry->size; i++) {
                if (numEntry->indices[i] == index) {
                    numEntry->indices[i] = numEntry->indices[numEntry->size - 1]; // Swap with last element
                    numEntry->size--;
                    break;
                }
            }
            if (numEntry->size == 0) {
                free(numEntry->indices);
                HASH_DEL(obj->numberToIndices, numEntry);
                free(numEntry);
            }
        }
        entry->number = number;
    } else {
        entry = malloc(sizeof(IndexToNumber));
        entry->index = index;
        entry->number = number;
        HASH_ADD_INT(obj->indexToNumbers, index, entry);
    }
    
    // Add index to the new number's mapping
    NumberToIndices * numEntry;
    HASH_FIND_INT(obj->numberToIndices, &number, numEntry);

    if (!numEntry) {
        numEntry = malloc(sizeof(NumberToIndices));
        numEntry->number = number;
        numEntry->size = 0;
        numEntry->capacity = 4;
        numEntry->indices = malloc(numEntry->capacity * sizeof(int));
        HASH_ADD_INT(obj->numberToIndices, number, numEntry);
    }
    
    // Resize array if needed
    if (numEntry->size == numEntry->capacity) {
        numEntry->capacity *= 2;
        numEntry->indices = realloc(numEntry->indices, numEntry->capacity * sizeof(int));
    }

    numEntry->indices[numEntry->size++] = index;
}

// Function to find the smallest index for a given number
int numberContainersFind(NumberContainers* obj, int number) {
    NumberToIndices * numEntry;
    HASH_FIND_INT(obj->numberToIndices, &number, numEntry);

    if (!numEntry || numEntry->size == 0) return -1;
    
    // Find the smallest index
    int minIndex = numEntry->indices[0];
    for (int i = 1; i < numEntry->size; i++) {
        if (numEntry->indices[i] < minIndex) {
            minIndex = numEntry->indices[i];
        }
    }

    return minIndex;
}

// Function to free memory allocated for NumberContainers
void numberContainersFree(NumberContainers* obj) {
    IndexToNumber * entry, * tmp1;
    
    HASH_ITER(hh, obj->indexToNumbers, entry, tmp1) {
        HASH_DEL(obj->indexToNumbers, entry);
        free(entry);
    }
    
    NumberToIndices * numEntry, * tmp2;

    HASH_ITER(hh, obj->numberToIndices, numEntry, tmp2) {
        free(numEntry->indices);
        HASH_DEL(obj->numberToIndices, numEntry);
        free(numEntry);
    }

    free(obj);
}

// Runtime: 1396ms 
// Memory: 134.24MB