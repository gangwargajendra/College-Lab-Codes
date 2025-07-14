import random
import time
import matplotlib.pyplot as plt
from collections import deque


class Puzzle:
    def __init__(self, size):
        self.n = size
        self.goal_state = tuple(range(1, size * size)) + (0,)
        self.moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right

    def generate_initial_states(self, num_states=10):
        states = []
        for _ in range(num_states):
            state = list(self.goal_state)
            random.shuffle(state)
            states.append(tuple(state))
        return states

    def find_zero(self, state):
        idx = state.index(0)
        return idx // self.n, idx % self.n

    def get_neighbors(self, state):
        zero_r, zero_c = self.find_zero(state)
        neighbors = []
        for dr, dc in self.moves:
            new_r, new_c = zero_r + dr, zero_c + dc
            if 0 <= new_r < self.n and 0 <= new_c < self.n:
                new_state = list(state)
                new_idx = new_r * self.n + new_c
                new_state[zero_r * self.n + zero_c], new_state[new_idx] = new_state[new_idx], new_state[
                    zero_r * self.n + zero_c]
                neighbors.append(tuple(new_state))
        return neighbors

    def bfs(self, start):
        queue = deque([(start, 0)])
        visited = set()
        while queue:
            state, depth = queue.popleft()
            if state == self.goal_state:
                return depth
            if state in visited:
                continue
            visited.add(state)
            for neighbor in self.get_neighbors(state):
                queue.append((neighbor, depth + 1))
        return -1

    def dfs(self, state, depth, max_depth, visited):
        if state == self.goal_state:
            return depth
        if depth >= max_depth or state in visited:
            return -1
        visited.add(state)
        for neighbor in self.get_neighbors(state):
            result = self.dfs(neighbor, depth + 1, max_depth, visited)
            if result != -1:
                return result
        visited.remove(state)
        return -1

    def iterative_deepening(self, start):
        depth = 0
        while True:
            visited = set()
            result = self.dfs(start, 0, depth, visited)
            if result != -1:
                return result
            depth += 1

    def run_experiment(self, max_n=4):
        sizes = range(2, max_n + 1)
        results = {"BFS": [], "DFS": [], "ID": []}
        for n in sizes:
            self.n = n
            states = self.generate_initial_states()
            bfs_times, dfs_times, id_times = [], [], []
            for state in states:
                for algo, time_list in zip([self.bfs, self.dfs, self.iterative_deepening],
                                           [bfs_times, dfs_times, id_times]):
                    start_time = time.time()

                    if algo == self.dfs:
                        # DFS requires more parameters, we provide depth, max_depth, and visited
                        result = algo(state, 0, 10, set())  # start with depth=0, max_depth=10, and an empty visited set
                    else:
                        # For BFS and Iterative Deepening, we just call them as normal
                        result = algo(state)

                    end_time = time.time()
                    time_list.append(end_time - start_time)
            results["BFS"].append(sum(bfs_times) / len(bfs_times))
            results["DFS"].append(sum(dfs_times) / len(dfs_times))
            results["ID"].append(sum(id_times) / len(id_times))
        return sizes, results

    def plot_results(self, sizes, results):
        plt.figure(figsize=(10, 6))
        for algo, times in results.items():
            plt.plot(sizes, times, marker='o', label=algo)
        plt.xlabel('Puzzle Size (n)')
        plt.ylabel('Avg. Time (s)')
        plt.title('Comparison of BFS, DFS, and Iterative Deepening')
        plt.legend()
        plt.show()


if __name__ == "__main__":
    puzzle = Puzzle(size=3)
    sizes, results = puzzle.run_experiment(max_n=4)
    puzzle.plot_results(sizes, results)
