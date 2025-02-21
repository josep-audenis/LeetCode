// Given a binary tree with the following rules:+
// · root.val == 0
// · For any treeNode:
// 	1. If treeNode.val has a value x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
// 	2. If treeNode.val has a value x and treeNode.right != null, then treeNode.right.val == 2 * x + 2

// Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.
// Implement the FindElements class:
// · FindElements(TreeNode* root) Initializes the object with a contaminated binary tree and recovers it.
// · bool find(int target) Returns true if the target value exists in the recovered binary tree. 

// - Example 1:
// Input:
// · ["FindElements","find","find"]
// · [[[-1,null,-1]],[1],[2]]
// Output:
// · [null,false,true]
// Explanation:
// FindElements findElements = new FindElements([-1,null,-1]); 
// findElements.find(1); // return False 
// findElements.find(2); // return True 

// - Example 2:
// Input:
// · ["FindElements","find","find","find"]
// · [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
// Output:
// · [null,true,true,false]
// Explanation:
// FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
// findElements.find(1); // return True
// findElements.find(3); // return True
// findElements.find(5); // return False

// - Example 3:
// Input:
// · ["FindElements","find","find","find","find"]
// · [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
// Output:
// · [null,true,false,false,true]
// Explanation:
// FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
// findElements.find(2); // return True
// findElements.find(3); // return False
// findElements.find(4); // return False
// findElements.find(5); // return True

// Constraints:
// · TreeNode.val == -1
// · The height of the binary tree is less than or equal to 20
// · The total number of nodes is between [1, 104]
// · Total calls of find() is between [1, 104]
// · 0 <= target <= 106

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 typedef struct {
    int * found;
    int n_elements;
} FindElements;

void search(FindElements * obj, struct TreeNode* node, int value) {
    if (obj == NULL) return;	// If node is empty end the search of that branch

    obj->found[obj->n_elements++] = value;	// Store the value in the array

    if (node->left) search(obj, node->left, (value * 2) + 1);	// Keep searching through the left branch
    if (node->right) search(obj, node->right, (value * 2) + 2);	// Keep searching through the right branch
}

FindElements* findElementsCreate(struct TreeNode* root) {
    FindElements * elements = malloc(sizeof(FindElements));
    elements->found = malloc(sizeof(int) * 10000);	// Reserve memory for the max possible amount of values
    elements->n_elements = 0;
    search(elements, root, 0);	// Start the search of all the values found in the tree (dfs)
    return elements;
}

bool findElementsFind(FindElements* obj, int target) {
    for (int i = 0; i < obj->n_elements; i++) {
        if (obj->found[i] == target) {
            return true;	// Return true if the target value is found
        }
    }
    return false;
}

void findElementsFree(FindElements* obj) {
    free(obj->found);
    free(obj);
}

/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);
 
 * findElementsFree(obj);
*/

// Time Complexity: O(n)
// Space Complexity: O(n)