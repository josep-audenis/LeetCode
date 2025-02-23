# Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.

# If there exist multiple answers, you can return any of them.

# - Example 1:
# Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
# Output: [1,2,3,4,5,6,7]

# - Example 2:
# Input: preorder = [1], postorder = [1]
# Output: [1]
 
# Constraints:
# · 1 <= preorder.length <= 30
# · 1 <= preorder[i] <= preorder.length
# · All the values of preorder are unique.
# · postorder.length == preorder.length
# · 1 <= postorder[i] <= postorder.length
# · All the values of postorder are unique.
# · It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal of the same binary tree.

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        n = len(preorder)
        
        index_post = [0] * (n + 1)  # Create an index lookup table for postorder values
        for index in range(n):
            index_post[postorder[index]] = index
        
        return self.construct(0, n - 1, 0, preorder, index_post)    # Start constructing the tree from the full range of preorder and postorder

    def construct(self, pre_start: int, pre_end: int, post_start: int, preorder: List[int], index_post: List[int]):
        
        if pre_start > pre_end: # Base case: if the range is invalid, return None
            return None

        if pre_start == pre_end:    # Base case: if there is only one element, return a TreeNode with that value
            return TreeNode(preorder[pre_start])

        left_root = preorder[pre_start + 1] # The next element in preorder is always the left subtree root
        nodes_left = index_post[left_root] - post_start + 1 # Determine the size of the left subtree using postorder index lookup
        
        root = TreeNode(preorder[pre_start])    # Create the root node
        root.left = self.construct(pre_start + 1, pre_start + nodes_left, post_start, preorder,  index_post)    # Recursively construct left and right subtrees
        root.right = self.construct(pre_start + nodes_left + 1, pre_end, post_start + nodes_left, preorder, index_post)

        return root

# Time Complexity: O(n)
# Space Complexity: O(n)