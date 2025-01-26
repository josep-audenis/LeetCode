// You are given a 0-indexed array of positive integers nums and a positive integer limit.
// In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
// 
// Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
// 
// An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.
//  
// - Example 1:
// Input: nums = [1,5,3,9,8], limit = 2
// Output: [1,3,5,8,9]
// Explanation: Apply the operation 2 times:
// - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
// - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// Note that it may be possible to get the same result by doing different operations.
// 
// - Example 2:
// Input: nums = [1,7,6,18,2,1], limit = 3
// Output: [1,6,7,18,1,2]
// Explanation: Apply the operation 3 times:
// - Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
// - Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
// - Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// 
// - Example 3:
// Input: nums = [1,7,28,19,10], limit = 3
// Output: [1,7,28,19,10]
// Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.
//  
// Constraints:
// · 1 <= nums.length <= 105
// · 1 <= nums[i] <= 109
// · 1 <= limit <= 109

int compare(const void *a, const void *b){                              //compare the first index of two arrays
    int *arr1 = (int *)a;
    int *arr2 = (int *)b;
    return (arr1[0] - arr2[0]);
}

int compare2(const void *a, const void *b){                             //compare two single values
    return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicographicallySmallestArray(int* nums, int numsSize, int limit, int* returnSize) {
    int *result = (int *)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;
    int sorted[numsSize][2]; 

    for (int i = 0; i < numsSize; i++){                                 //initialize the values of the sorted array with the values of nums array and their indices
        sorted[i][0] = nums[i];
        sorted[i][1] = i;
    }

    qsort(sorted, numsSize, sizeof(sorted[0]), compare);                //sort the array using compare method

    int indices[numsSize];                                              //temporary array to store indices of elements in the current group
    int i = 0; 
    while (i < numsSize){
        int size = 0;         
        int prev = sorted[i][0]; 
        while(i < numsSize && sorted[i][0] <= (prev + limit)){          //group elements whose values differ by at most `limit`
            indices[size++] = sorted[i][1];                             //add the index of the current element to the group
            prev = sorted[i][0];
            i++;
        }
        
        qsort(indices, size, sizeof(int), compare2);                    //sort the indices of the current group to maintain lexicographical order
        
        for (int j = 0, k = i - size; j < size; j++, k++){
            result[indices[j]] = sorted[k][0];                          //assign the sorted value to its original position
        }   
    }

    return result;
}

// Runtime: 78ms 
// Memory: 102.45MB