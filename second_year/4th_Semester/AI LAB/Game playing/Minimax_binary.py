# Binary tree creation and Minimax with Alpha-Beta Pruning

leaf_values = [8, 5, 3, 9, 9, 7, 2, 4, 1, 8, 6, 9, 9, 9, 3, 4]
depth = 4  # Number of plies until leaves (4 moves yield 16 leaves)

class Node:
    def __init__(self, value=None, left=None, right=None):
        self.value = value
        self.left  = left
        self.right = right

def build_tree(leaf_values):
    # Build a full binary tree bottom-up from the leaf values.
    nodes = [Node(value=val) for val in leaf_values]
    while len(nodes) > 1:
        next_level = []
        for i in range(0, len(nodes), 2):
            left = nodes[i]
            right = nodes[i+1]
            parent = Node(left=left, right=right)
            next_level.append(parent)
        nodes = next_level
    return nodes[0]

def minimax_tree(node, maximizingPlayer, alpha=-float('inf'), beta=float('inf')):
    # Base case: leaf node, its value is already set.
    if node.left is None and node.right is None:
        return node.value, []
    
    if maximizingPlayer:
        best_value = -float('inf')
    else:
        best_value = float('inf')
    best_path = []
    
    # Explore left (index 0) and right (index 1) children.
    for i, child in enumerate([node.left, node.right]):
        val, path = minimax_tree(child, not maximizingPlayer, alpha, beta)
        
        if maximizingPlayer:
            if val > best_value:
                best_value = val
                best_path = [i] + path
            alpha = max(alpha, best_value)
        else:
            if val < best_value:
                best_value = val
                best_path = [i] + path
            beta = min(beta, best_value)
        
        # Perform Alpha-Beta pruning if possible.
        if beta <= alpha:
            break
    
    return best_value, best_path

# Build the binary tree from the leaf_values list.
tree_root = build_tree(leaf_values)

# Now compute the best optimal path using minimax with alpha-beta pruning.
root_value, optimal_path = minimax_tree(tree_root, True)
print(f"Computed root value: {root_value}")
print(f"Optimal path for MAX (0=left, 1=right): {optimal_path}")