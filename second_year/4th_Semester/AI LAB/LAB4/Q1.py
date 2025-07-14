import time
import random
from collections import deque
import matplotlib.pyplot as plt

# Helper function to find possible moves for the blank tile (0)
def get_blank_moves(blank_position, grid_size):
    row = blank_position // grid_size
    col = blank_position % grid_size
    moves = []
    # Check possible moves in all four directions
    if row > 0:
        moves.append(blank_position - grid_size)  # Move up
    if row < grid_size - 1:
        moves.append(blank_position + grid_size)  # Move down
    if col > 0:
        moves.append(blank_position - 1)          # Move left
    if col < grid_size - 1:
        moves.append(blank_position + 1)          # Move right
    return moves

# Generate a random solvable puzzle state by making random moves from the solved state
def create_scrambled_puzzle(grid_size, num_moves=1000):
    solved_state = list(range(1, grid_size*grid_size)) + [0]
    current_state = solved_state.copy()
    blank_pos = grid_size*grid_size - 1  # Start with blank at bottom-right
    
    for _ in range(num_moves):
        possible_moves = get_blank_moves(blank_pos, grid_size)
        new_blank_pos = random.choice(possible_moves)
        # Swap blank tile with adjacent tile
        current_state[blank_pos], current_state[new_blank_pos] = current_state[new_blank_pos], current_state[blank_pos]
        blank_pos = new_blank_pos
    
    return tuple(current_state)

# Breadth-First Search implementation
def breadth_first_search(start_state, target_state, grid_size):
    start_time = time.time()
    visited = set()
    queue = deque([(start_state, 0)])
    visited.add(start_state)
    
    while queue:
        current_state, steps = queue.popleft()
        
        # Check if we've reached the solution
        if current_state == target_state:
            return time.time() - start_time
        
        # Find where the blank tile (0) is located
        blank_pos = current_state.index(0)
        
        # Generate all possible next states
        for move in get_blank_moves(blank_pos, grid_size):
            new_state = list(current_state)
            new_state[blank_pos], new_state[move] = new_state[move], new_state[blank_pos]
            new_state_tuple = tuple(new_state)
            
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                queue.append((new_state_tuple, steps + 1))
        
        # Check timeout after each iteration
        if time.time() - start_time > 60:
            return None
    
    return None

# Depth-First Search implementation
def depth_first_search(start_state, target_state, grid_size):
    start_time = time.time()
    visited = set()
    stack = [(start_state, 0)]
    visited.add(start_state)
    
    while stack:
        current_state, steps = stack.pop()
        
        if current_state == target_state:
            return time.time() - start_time
        
        blank_pos = current_state.index(0)
        
        # Explore moves in reverse order to maintain same order as BFS
        for move in reversed(get_blank_moves(blank_pos, grid_size)):
            new_state = list(current_state)
            new_state[blank_pos], new_state[move] = new_state[move], new_state[blank_pos]
            new_state_tuple = tuple(new_state)
            
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                stack.append((new_state_tuple, steps + 1))
        
        if time.time() - start_time > 60:
            return None
    
    return None

# Iterative Deepening Search implementation
def iterative_deepening_search(start_state, target_state, grid_size):
    start_time = time.time()
    depth_limit = 0
    
    while True:
        # Search with increasing depth limits
        result = depth_limited_search(start_state, target_state, grid_size, depth_limit, start_time)
        if result is not None:
            return result
        if time.time() - start_time > 60:
            return None
        depth_limit += 1

# Helper function for depth-limited DFS used in Iterative Deepening
def depth_limited_search(start_state, target_state, grid_size, max_depth, start_time):
    visited = set()
    # Stack elements: (state, current_depth, is_visited_flag)
    stack = [(start_state, 0, False)]
    
    while stack:
        current_state, depth, is_visited = stack.pop()
        
        # Cleanup visited states when backtracking
        if is_visited:
            visited.discard(current_state)
            continue
        
        # Check timeout and depth limit
        if time.time() - start_time > 60:
            return None
        if current_state == target_state:
            return time.time() - start_time
        if depth >= max_depth:
            continue
        if current_state in visited:
            continue
            
        visited.add(current_state)
        # Mark for cleanup when backtracking
        stack.append((current_state, depth, True))
        
        blank_pos = current_state.index(0)
        for move in reversed(get_blank_moves(blank_pos, grid_size)):
            new_state = list(current_state)
            new_state[blank_pos], new_state[move] = new_state[move], new_state[blank_pos]
            new_state_tuple = tuple(new_state)
            stack.append((new_state_tuple, depth + 1, False))
    
    return None

def main():
    # Test different puzzle sizes (3x3 and 4x4)
    puzzle_sizes = [2,3]
    algorithms = {
        'BFS': breadth_first_search,
        'DFS': depth_first_search,
        'ID': iterative_deepening_search
    }
    
    # Store results for each algorithm and puzzle size
    results = {}
    
    for algo in algorithms:
        results[algo] = {}
        for size in puzzle_sizes:
            results[algo][size] = []
    
    for size in puzzle_sizes:
        print(f"\n=== Testing {size}x{size} puzzles ===")
        
        number = list(range(1, size*size))
        target_state = tuple(number + [0])
        print("Generating 10 random puzzles...")
        puzzles = [create_scrambled_puzzle(size) for _ in range(10)]

        valid_puzzles = 0
        
        for puzzle_num, puzzle in enumerate(puzzles, 1):
            print(f"\nTesting puzzle #{puzzle_num}")
            print(puzzle)
            valid = True
            times = {}
            
            for algo_name, algorithm in algorithms.items():
                print(f"  Running {algo_name}...", end=" ")
                start_time = time.time()
                solve_time = algorithm(puzzle, target_state, size)
                
                if solve_time is None:
                    print(f"TIMEOUT (60s)")
                    valid = False
                    break
                else:
                    print(f"Solved in {solve_time:.2f}s")
                    times[algo_name] = solve_time
            
            if valid:
                valid_puzzles += 1
                for algo_name, t in times.items():
                    results[algo_name][size].append(t)
            else:
                print("  Puzzle invalid (some algorithms timed out)")
        
        print(f"\nValid puzzles for {size}x{size}: {valid_puzzles}/10")
    
    # Calculate average times
    avg_times = {algo: {} for algo in algorithms}
    for algo_name in algorithms:
        for size in puzzle_sizes:
            times = results[algo_name][size]
            if times:
                avg_times[algo_name][size] = sum(times)/len(times)
            else:
                avg_times[algo_name][size] = None
    
    # Plot results
    plt.figure(figsize=(10, 6))
    markers = {'BFS': 'o', 'DFS': 's', 'ID': '^'}
    colors = {'BFS': 'blue', 'DFS': 'red', 'ID': 'green'}
    
    for algo_name in algorithms:
        x_values = []
        y_values = []
        for size in puzzle_sizes:
            avg = avg_times[algo_name].get(size)
            if avg is not None:
                x_values.append(size)
                y_values.append(avg)
        
        plt.plot(x_values, y_values, 
                 marker=markers[algo_name], 
                 color=colors[algo_name],
                 label=algo_name)
    
    plt.xlabel('Puzzle Size (n)')
    plt.ylabel('Average Time (seconds)')
    plt.title('Puzzle Solving Performance Comparison')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()