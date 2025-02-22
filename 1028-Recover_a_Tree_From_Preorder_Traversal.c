//  We run a preorder depth-first search (DFS) on the root of a binary tree.

//  At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.

//  If a node has only one child, that child is guaranteed to be the left child.

//  Given the output traversal of this traversal, recover the tree and return its root.

//  - Example 1:
//  Input: traversal = "1-2--3--4-5--6--7"
//  Output: [1,2,5,3,4,6,7]

//  - Example 2:
//  Input: traversal = "1-2--3---4-5--6---7"
//  Output: [1,2,5,3,null,6,null,4,null,7]

//  - Example 3:
//  Input: traversal = "1-401--349---90--88"
//  Output: [1,401,null,349,88,90]

//  Constraints:
//  · The number of nodes in the original tree is in the range [1, 1000].
//  · 1 <= Node.val <= 10^9

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* recoverFromPreorder(char* traversal) {
    struct TreeNode ** depths = malloc(sizeof(struct TreeNode) * 1001); 

    int index = 0;
    int length = strlen(traversal);

    while (index < length) {

        int depth = 0;

        while (index < length && traversal[index] == '-') { // Check the depth of the node
            depth++;
            index++;
        }

        int value = 0;

        while (index < length && traversal[index] != '-') { // Get the value of the node
            value = value * 10 + (traversal[index] - '0');     
            index++;
        }

        struct TreeNode * node = malloc(sizeof(struct TreeNode));

        node->val = value;  // Create an insatnce of the node
        node->left = NULL;
        node->right = NULL;

        depths[depth] = node;   // Store the node to it's depth position

        if (depth > 0) {
            struct TreeNode * parent = depths[depth - 1];   // Get the node parent
            if (parent->left == NULL) { // If there is no left child, assign it to the left
                parent->left = node;
            } else {
                parent->right = node;   // If there is left child, assign it to the right
            }
        }
    }

    struct TreeNode * root = depths[0]; // Store the root node
    free(depths);   // Free the node list (not the tree)
    return root;
}

// Time Complexity: O(n)
// Space Complexity: O(n)