# Minimax with Alpha-Beta Pruning on a Binary Game Tree

leaf_values = [8, 5, 3, 9, 9, 7, 2, 4, 1, 8, 6, 9, 9, 9, 3, 4]
depth = 4  # Number of plies until leaf (4 moves down yields 16 leaves)

def minimax(values, depth, maximizingPlayer, alpha=-float('inf'), beta=float('inf')):
    # Base case: at leaf, only one value
    if depth == 0:
        return values[0], []
    
    half = len(values) // 2
    # Initialize best values
    if maximizingPlayer:
        best_value = -float('inf')
    else:
        best_value = float('inf')
    best_path = []
    
    # Explore left (0) and right (1) branches
    for i in range(2):
        child_values = values[i * half:(i + 1) * half]
        val, path = minimax(child_values, depth - 1, not maximizingPlayer, alpha, beta)
        
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
        
        # Alpha-beta pruning
        if beta <= alpha:
            break
    
    return best_value, best_path

# Execute and display results
root_value, optimal_path = minimax(leaf_values, depth, True)
print(f"Computed root value: {root_value}")
print(f"Optimal path for MAX (0=left, 1=right): {optimal_path}")
