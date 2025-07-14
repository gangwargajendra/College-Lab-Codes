import math
import random


def calCost(tour, costMatrix):
    total = 0
    for i in range(len(tour) - 1):
        a = tour[i]
        b = tour[i + 1]
        total += costMatrix[a][b]
    return total


def genInitialTour(n):
    cities = list(range(1, n))
    random.shuffle(cities)
    return [0] + cities + [0]


def genRandomNeighbor(tour):
    middleIndices = list(range(1, len(tour) - 1))
    if len(middleIndices) < 2:
        return tour.copy()
    i, j = random.sample(middleIndices, 2)
    newTour = tour.copy()
    newTour[i], newTour[j] = newTour[j], newTour[i]
    return newTour


def simulatedAnnealing(n, costMatrix, T=1000.0, alpha=0.995, K=None):
    print("Simulated annealing starts...")
    if K is None:
        K = 100 * n * n
    crntTour = genInitialTour(n)
    crntCost = calCost(crntTour, costMatrix)
    bestTour = crntTour.copy()
    bestCost = crntCost
    for _ in range(K):
        neighbor = genRandomNeighbor(crntTour)
        neighborCost = calCost(neighbor, costMatrix)
        delta = neighborCost - crntCost
        if delta < 0 or (random.random() < math.exp(-delta / T)):
            crntTour = neighbor
            crntCost = neighborCost
            if crntCost < bestCost:
                bestTour = crntTour.copy()
                bestCost = crntCost
        T *= alpha
    print("Simulated annealing terminates...")
    return bestTour, bestCost


def main():
    print("Enter size of matrix : ")
    n = int(input())
    costMatrix = []
    print("Enter cost matrix : ")
    for _ in range(n):
        row = list(map(int, input().split()))
        costMatrix.append(row)

    tour, cost = simulatedAnnealing(n, costMatrix)
    print("\nSimulated Annealing Solution:")
    print("Route:", " -> ".join(map(str, tour)))
    print("Cost:", cost)


if __name__ == "__main__":
    main()