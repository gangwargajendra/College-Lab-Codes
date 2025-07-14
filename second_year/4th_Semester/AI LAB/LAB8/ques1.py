import random


def genInitialPolulation(populationSize, n):
    population = []
    for _ in range(populationSize):
        individual = list(range(1, n))
        random.shuffle(individual)
        population.append([0] + individual + [0])
    return population

def calCost(individual, costMatrix):
    cost = 0
    n = len(individual)
    for i in range(1, n):
        a = individual[i]
        b = individual[i-1]
        cost += costMatrix[a][b]
    return cost


def tournamentSelection(population, fitnesses, tournamentSize):
    selected = []
    popSize = len(population)
    for _ in range(popSize):
        contestants = []
        for _ in range(tournamentSize):
            idx = random.randint(0, popSize-1)
            contestant = (population[idx], fitnesses[idx])
            contestants.append(contestant)

        best = contestants[0]
        for contestant in contestants:
            if contestant[1] < best[1]:
                best = contestant
        selected.append(best[0])
    return selected

# for ordering crossover
def ox_crossover(parent1, parent2):
    size = len(parent1)
    # Choose two crossover points  0 1 2 3 0
    start, end = sorted(random.sample(range(1, size - 1), 2))

    child1 = [0] + [None] * (size - 2) + [0]
    child2 = [0] + [None] * (size - 2) + [0]

    child1[start:end + 1] = parent1[start:end + 1]
    child2[start:end + 1] = parent2[start:end + 1]

    def fill_child(child, parent):
        fillingIndex = end + 1
        fillOrder = parent[end+1:size-1] + parent[1:end+1]

        for gene in fillOrder:
            if gene not in child:
                if fillingIndex >= size-1:
                    fillingIndex = 1
                child[fillingIndex] = gene
                fillingIndex += 1
        return child

    child1 = fill_child(child1, parent2)
    child2 = fill_child(child2, parent1)

    return child1, child2


def mutate_tsp(individual):
    if len(individual) <= 2:
        return individual
    # Corrected range to exclude the last element (0)
    i, j = random.sample(range(1, len(individual)-1), 2)
    individual[i], individual[j] = individual[j], individual[i]
    return individual


def solveTSP(n, costMatrix):
    popSize = 100
    generation = 500
    mutationRate = 0.2
    tournamentSize = 5
    elitism = True

    population = genInitialPolulation(popSize, n)
    bestIndividual = None
    bestDistance = float('inf')

    for gen in range(generation):
        fitness = []
        for ind in population:
            dis = calCost(ind, costMatrix)
            fitness.append(dis)
        crntBest = min(fitness)
        crntBestIndex = fitness.index(crntBest)
        if crntBest < bestDistance:
            bestDistance = crntBest
            bestIndividual = population[crntBestIndex].copy()
            print(f"generation {gen + 1}: New best distance : {bestDistance}")

        selected = tournamentSelection(population, fitness, tournamentSize)
        offspring = []
        for i in range(0, len(selected)-1, 2):
            parent1 = selected[i]
            parent2 = selected[i+1]
            child1, child2 = ox_crossover(parent1, parent2)
            offspring.append(child1)
            offspring.append(child2)

        for i in range(len(offspring)):
            if random.random() < mutationRate:
                offspring[i] = mutate_tsp(offspring[i])

        if elitism and bestIndividual is not None:
            offspringFitness = []
            for ind in offspring:
                distance = calCost(ind, costMatrix)
                offspringFitness.append(distance)
            worstIndx = offspringFitness.index((max(offspringFitness)))
            offspring[worstIndx] = bestIndividual.copy()

        population = offspring
    return bestIndividual, bestDistance


def main():
    n = int(input("Enter no of cities : "))
    costMatrix = []
    print("Enter cost Matrix : ")
    for _ in range(n):
        row = list(map(int, input().split()))
        costMatrix.append(row)
    print(costMatrix)

    bestRoute, bestDistance = solveTSP(n, costMatrix)
    print("\nTSP Solution : ")
    print(f"Route : {' -> '.join(map(str, bestRoute))}")
    print(f"Distance : {bestDistance}")


if __name__ == '__main__' :
    main()