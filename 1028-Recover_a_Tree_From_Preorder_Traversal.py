# We run a preorder depth-first search (DFS) on the root of a binary tree.

# At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.

# If a node has only one child, that child is guaranteed to be the left child.

# Given the output traversal of this traversal, recover the tree and return its root.

# - Example 1:
# Input: traversal = "1-2--3--4-5--6--7"
# Output: [1,2,5,3,4,6,7]

# - Example 2:
# Input: traversal = "1-2--3---4-5--6---7"
# Output: [1,2,5,3,null,6,null,4,null,7]

# - Example 3:
# Input: traversal = "1-401--349---90--88"
# Output: [1,401,null,349,88,90]

# Constraints:
# · The number of nodes in the original tree is in the range [1, 1000].
# · 1 <= Node.val <= 109

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        depths = [] # List with rightest node found in the tree by depth
        index = 0
        length = len(traversal)
        
        while index < length:   # Iterate through all the string
            
            depth, index = self.getDepth(traversal, index)  # Get the depth of the current node

            value, index = self.getValue(traversal, index, length)  # Get the value of the current node

            node = TreeNode(value, None, None)  # Create the TreeNode object

            if depth < len(depths):
                depths[depth] = node    # Replace the node in the depths list
            else:
                depths.append(node) # If new depth append the node

            if depth > 0:
                parent = depths[depth - 1]  # Search for the parent
                if parent.left is None: # Assign the child deppending on current children
                    parent.left = node
                else:
                    parent.right = node
            
        return depths[0]    # Return root

    def getValue(self, traversal: str, index: int, length: int):
        value = 0
        while index < length and traversal[index].isdigit():
            value = value * 10 + int(traversal[index])  # Convert the string number to an int
            index += 1
        
        return value, index

    def getDepth(self, traversal: str, index: int):
        depth = 0
        while traversal[index] == "-":  # Count the ammount of "-" before a number
            depth += 1
            index += 1

        return depth, index

# Time Complexity: O(n)
# Space Complexity: O(n)