import  random

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


def main():
    n = int(input("Enter no of cities : "))
    costMatrix = []
    print("Enter cost Matrix : ")
    for _ in range(n):
        row = list(map(int, input().split()))
        costMatrix.append(row)
    print(costMatrix)
    best_route, best_distance = solve_tsp(n, costMatrix)
    print("\nTSP Solution:")
    print(f"Route: {' -> '.join(map(str, best_route))} -> 0")
    print(f"Distance: {best_distance}")


if __name__ == '__main__' :
    main()