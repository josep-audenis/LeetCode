// Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.
// 
// Implement the ProductOfNumbers class:
// · ProductOfNumbers() Initializes the object with an empty stream.
// · void add(int num) Appends the integer num to the stream.
// · int getProduct(int k) Returns the product of the last k numbers in the current list. You can assume that always the current list has at least k numbers.
// 
// The test cases are generated so that, at any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.
// 
// Example:
// Input
// ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
// [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
// Output
// [null,null,null,null,null,null,20,40,0,null,32]
// Explanation
// ProductOfNumbers productOfNumbers = new ProductOfNumbers();
// productOfNumbers.add(3);        // [3]
// productOfNumbers.add(0);        // [3,0]
// productOfNumbers.add(2);        // [3,0,2]
// productOfNumbers.add(5);        // [3,0,2,5]
// productOfNumbers.add(4);        // [3,0,2,5,4]
// productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
// productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
// productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
// productOfNumbers.add(8);        // [3,0,2,5,4,8]
// productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32 
// 
// Constraints:
// · 0 <= num <= 100
// · 1 <= k <= 4 * 104
// · At most 4 * 104 calls will be made to add and getProduct.
// · The product of the stream at any point in time will fit in a 32-bit integer.
//  
// Follow-up: Can you implement both GetProduct and Add to work in O(1) time complexity instead of O(k) time complexity?

typedef struct {
    uint32_t *products; 
    int length;         
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers *obj = malloc(sizeof(ProductOfNumbers));

    obj->products = malloc(sizeof(uint32_t) * 40000);

    obj->products[0] = 1;															// Initialize the first element as 1 
    obj->length = 1;

    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {																	// If a 0 is added, reset the list because any future product would be 0
        obj->length = 1;															
        obj->products[0] = 1;
    } else {
        obj->products[obj->length] = num * obj->products[obj->length - 1];			// Multiply the number by the last accumulated product and store it
        obj->length++;        
    }
    return;
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (obj->length - 1 < k) {
        return 0;																	// If there are fewer than k valid elements, it means a 0 was in the sequence, so the product is 0
    } 
    
    return obj->products[obj->length - 1] / obj->products[obj->length - k - 1]; 	// Retrieve the product by dividing the last stored product by the accumulated product k positions back
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->products); 															// Free the memory of the products array
    free(obj);           															// Free the memory of the structure
}

/**
 * Example usage:
 * ProductOfNumbers* obj = productOfNumbersCreate();
 * productOfNumbersAdd(obj, num);
 * int param_2 = productOfNumbersGetProduct(obj, k);
 * productOfNumbersFree(obj);
 */

// Runtime: 15ms 
// Memory: 50.59MB