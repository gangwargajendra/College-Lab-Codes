import random
import sys


# Function to get input lines interactively
def get_input_lines():
    print("Please enter your input (press Enter twice to finish):")
    input_lines = []
    while True:
        line = input().strip()
        if line:
            input_lines.append(line)
        else:
            if input_lines:  # Ensure at least one line is entered
                break
    return input_lines


# TSP Functions (unchanged)
def initialize_population_tsp(pop_size, n):
    population = []
    for _ in range(pop_size):
        individual = [0] + random.sample(range(1, n), n - 1)
        population.append(individual)
    return population


def calculate_distance(individual, cost_matrix):
    distance = 0
    n = len(individual)
    for i in range(n - 1):
        distance += cost_matrix[individual[i]][individual[i + 1]]
    distance += cost_matrix[individual[-1]][individual[0]]
    return distance


def tournament_selection(population, fitnesses, tournament_size):
    selected = []
    for _ in range(len(population)):
        contestants = random.sample(list(zip(population, fitnesses)), tournament_size)
        winner = min(contestants, key=lambda x: x[1])
        selected.append(winner[0])
    return selected


def ox_crossover(parent1, parent2):
    size = len(parent1)
    if size <= 3:
        return parent1.copy(), parent2.copy()
    start, end = sorted(random.sample(range(1, size - 1), 2))
    child1 = [0] + [None] * (size - 1)
    child2 = [0] + [None] * (size - 1)
    child1[start:end + 1] = parent1[start:end + 1]
    child2[start:end + 1] = parent2[start:end + 1]

    def fill_child(child, parent):
        current_pos = end + 1
        for gene in (parent[end + 1:] + parent[1:end + 1]):
            if gene not in child[start:end + 1]:
                while current_pos < size and child[current_pos] is not None:
                    current_pos += 1
                if current_pos >= size:
                    current_pos = 1
                while child[current_pos] is not None:
                    current_pos += 1
                    if current_pos >= size:
                        current_pos = 1
                child[current_pos] = gene
        return child

    child1 = fill_child(child1, parent2)
    child2 = fill_child(child2, parent1)
    return child1, child2


def mutate_tsp(individual):
    if len(individual) <= 2:
        return individual
    i, j = random.sample(range(1, len(individual)), 2)
    individual[i], individual[j] = individual[j], individual[i]
    return individual


def solve_tsp(n, cost_matrix):
    pop_size = 100
    generations = 500
    mutation_rate = 0.2
    tournament_size = 5
    elitism = True

    population = initialize_population_tsp(pop_size, n)
    best_individual = None
    best_distance = float('inf')

    for gen in range(generations):
        fitnesses = [calculate_distance(ind, cost_matrix) for ind in population]
        current_best = min(fitnesses)
        current_best_idx = fitnesses.index(current_best)
        if current_best < best_distance:
            best_distance = current_best
            best_individual = population[current_best_idx].copy()
            print(f"Generation {gen + 1}: New best distance: {best_distance}")

        selected = tournament_selection(population, fitnesses, tournament_size)
        offspring = []
        for i in range(0, len(selected) - 1, 2):
            parent1 = selected[i]
            parent2 = selected[i + 1]
            child1, child2 = ox_crossover(parent1, parent2)
            offspring.append(child1)
            offspring.append(child2)

        for i in range(len(offspring)):
            if random.random() < mutation_rate:
                offspring[i] = mutate_tsp(offspring[i])

        if elitism and best_individual is not None:
            offspring_fitness = [calculate_distance(ind, cost_matrix) for ind in offspring]
            worst_idx = offspring_fitness.index(max(offspring_fitness))
            offspring[worst_idx] = best_individual.copy()

        population = offspring

    return best_individual, best_distance


# OPF Functions (unchanged)
def initialize_population_opf(pop_size, m, pmin, pmax):
    population = []
    for _ in range(pop_size):
        individual = [random.uniform(pmin[i], pmax[i]) for i in range(m)]
        population.append(individual)
    return population


def calculate_opf_fitness(individual, a, b, c, pd, pmin, pmax):
    cost = sum(a[i] + b[i] * pgi + c[i] * (pgi ** 2) for i, pgi in enumerate(individual))
    total_p = sum(individual)
    target = 1.05 * pd
    penalty = abs(total_p - target) * 1e6
    for i in range(len(individual)):
        if individual[i] < pmin[i]:
            penalty += (pmin[i] - individual[i]) * 1e6
        elif individual[i] > pmax[i]:
            penalty += (individual[i] - pmax[i]) * 1e6
    return cost + penalty


def tournament_selection_opf(population, fitnesses, tournament_size):
    selected = []
    for _ in range(len(population)):
        contestants = random.sample(list(zip(population, fitnesses)), tournament_size)
        winner = min(contestants, key=lambda x: x[1])
        selected.append(winner[0])
    return selected


def blx_alpha_crossover(parent1, parent2, alpha, pmin, pmax):
    child1 = []
    child2 = []
    for i in range(len(parent1)):
        x = min(parent1[i], parent2[i])
        y = max(parent1[i], parent2[i])
        d = y - x
        lower = max(x - alpha * d, pmin[i])
        upper = min(y + alpha * d, pmax[i])
        c1 = random.uniform(lower, upper)
        c2 = random.uniform(lower, upper)
        child1.append(c1)
        child2.append(c2)
    return child1, child2


def mutate_opf(individual, mutation_strength, pmin, pmax):
    mutated = []
    for i in range(len(individual)):
        new_val = individual[i] + random.gauss(0, mutation_strength)
        new_val = max(pmin[i], min(new_val, pmax[i]))
        mutated.append(new_val)
    return mutated


def solve_opf(m, pd, a, b, c, pmin, pmax):
    pop_size = 100
    generations = 500
    mutation_rate = 0.1
    mutation_strength = 1.0
    tournament_size = 5
    alpha = 0.3
    elitism = True

    population = initialize_population_opf(pop_size, m, pmin, pmax)
    best_individual = None
    best_fitness = float('inf')

    for gen in range(generations):
        fitnesses = [calculate_opf_fitness(ind, a, b, c, pd, pmin, pmax) for ind in population]
        current_best = min(fitnesses)
        current_best_idx = fitnesses.index(current_best)
        if current_best < best_fitness:
            best_fitness = current_best
            best_individual = population[current_best_idx].copy()
            actual_cost = sum(a[i] + b[i] * pgi + c[i] * (pgi ** 2) for i, pgi in enumerate(best_individual))
            print(f"Generation {gen + 1}: New best cost: {actual_cost:.2f}")

        selected = tournament_selection_opf(population, fitnesses, tournament_size)
        offspring = []
        for i in range(0, len(selected) - 1, 2):
            parent1 = selected[i]
            parent2 = selected[i + 1]
            child1, child2 = blx_alpha_crossover(parent1, parent2, alpha, pmin, pmax)
            offspring.append(child1)
            offspring.append(child2)

        for i in range(len(offspring)):
            if random.random() < mutation_rate:
                offspring[i] = mutate_opf(offspring[i], mutation_strength, pmin, pmax)

        if elitism and best_individual is not None:
            offspring_fitness = [calculate_opf_fitness(ind, a, b, c, pd, pmin, pmax) for ind in offspring]
            worst_idx = offspring_fitness.index(max(offspring_fitness))
            offspring[worst_idx] = best_individual.copy()

        population = offspring

    actual_cost = sum(a[i] + b[i] * pgi + c[i] * (pgi ** 2) for i, pgi in enumerate(best_individual))
    return best_individual, actual_cost


# Main Program
def main():
    input_lines = get_input_lines()

    if not input_lines:
        print("No input provided.")
        return

    first_line = input_lines[0].split()
    if len(first_line) == 1:
        n = int(first_line[0])
        cost_matrix = []
        for line in input_lines[1:1 + n]:
            row = list(map(int, line.split()))
            cost_matrix.append(row)
        best_route, best_distance = solve_tsp(n, cost_matrix)
        print("\nTSP Solution:")
        print(f"Route: {' -> '.join(map(str, best_route))} -> 0")
        print(f"Distance: {best_distance}")
    else:
        m, pd = map(float, first_line)
        m = int(m)
        pd = float(pd)
        a, b, c, pmin, pmax = [], [], [], [], []
        for line in input_lines[1:1 + m]:
            parts = list(map(float, line.split()))
            a.append(parts[0])
            b.append(parts[1])
            c.append(parts[2])
            pmin.append(parts[3])
            pmax.append(parts[4])
        best_output, best_cost = solve_opf(m, pd, a, b, c, pmin, pmax)
        print("\nOPF Solution:")
        print(f"Generator Outputs: {[round(p, 2) for p in best_output]}")
        print(f"Cost: {round(best_cost, 2)}")


if __name__ == "__main__":
    main()