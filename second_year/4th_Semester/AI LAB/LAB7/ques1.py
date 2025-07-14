import math
import random


def calculate_cost(tour, cost_matrix):
    total = 0
    for i in range(len(tour) - 1):
        a = tour[i]
        b = tour[i + 1]
        total += cost_matrix[a][b]
    return total


def generate_initial_tour(n):
    cities = list(range(1, n))
    random.shuffle(cities)
    return [0] + cities + [0]


def generate_all_neighbors(tour):
    neighbors = []
    middle_length = len(tour) - 2
    for i in range(1, len(tour) - 1):
        for j in range(i + 1, len(tour) - 1):
            new_tour = tour.copy()
            new_tour[i], new_tour[j] = new_tour[j], new_tour[i]
            neighbors.append(new_tour)
    return neighbors


def hill_climbing(n, cost_matrix):
    print("Hill-climbing starts...")
    current_tour = generate_initial_tour(n)
    current_cost = calculate_cost(current_tour, cost_matrix)
    while True:
        neighbors = generate_all_neighbors(current_tour)
        if not neighbors:
            break
        best_neighbor = None
        best_neighbor_cost = float('inf')
        for neighbor in neighbors:
            cost = calculate_cost(neighbor, cost_matrix)
            if cost < best_neighbor_cost:
                best_neighbor_cost = cost
                best_neighbor = neighbor
        if best_neighbor_cost < current_cost:
            current_tour = best_neighbor
            current_cost = best_neighbor_cost
        else:
            break
    print("hill climbing terminates...")
    return current_tour, current_cost


def generate_random_neighbor(tour):
    middle_part_indices = list(range(1, len(tour) - 1))
    if len(middle_part_indices) < 2:
        return tour.copy()
    i, j = random.sample(middle_part_indices, 2)
    new_tour = tour.copy()
    new_tour[i], new_tour[j] = new_tour[j], new_tour[i]
    return new_tour


def simulated_annealing(n, cost_matrix, T=1000.0, alpha=0.995, K=None):
    print("Simulated annealing starts...")
    if K is None:
        K = 100 * n * n
    current_tour = generate_initial_tour(n)
    current_cost = calculate_cost(current_tour, cost_matrix)
    best_tour = current_tour.copy()
    best_cost = current_cost
    for _ in range(K):
        neighbor = generate_random_neighbor(current_tour)
        neighbor_cost = calculate_cost(neighbor, cost_matrix)
        delta = neighbor_cost - current_cost
        if delta < 0 or (random.random() < math.exp(-delta / T)):
            current_tour = neighbor
            current_cost = neighbor_cost
            if current_cost < best_cost:
                best_tour = current_tour.copy()
                best_cost = current_cost
        T *= alpha
    print("Simulated annealing terminates...")
    return best_tour, best_cost


def main():
    print("Code starts...")
    print("Enter size of matrix(no of cities) : ")
    n = int(input())
    cost_matrix = []
    print("Enter cost matrix : ")
    for _ in range(n):
        row = list(map(int, input().split()))
        cost_matrix.append(row)

    # Hill Climbing Solution
    hc_tour, hc_cost = hill_climbing(n, cost_matrix)
    print("Hill Climbing Solution:")
    print("Route:", " -> ".join(map(str, hc_tour)))
    print("Cost:", hc_cost)

    # Simulated Annealing Solution
    sa_tour, sa_cost = simulated_annealing(n, cost_matrix)
    print("\nSimulated Annealing Solution:")
    print("Route:", " -> ".join(map(str, sa_tour)))
    print("Cost:", sa_cost)


if __name__ == "__main__":
    main()