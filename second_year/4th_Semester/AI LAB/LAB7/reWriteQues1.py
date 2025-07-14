from LAB7.ques1 import simulated_annealing


def main():
    print("Code starts...")
    print("Enter size of matrix(no of cities) : ")
    n = int(input())
    costMatrix = []
    print("Enter cost matrix : ")
    for _ in range(n):
        row = list(map(int, input().split()))
        costMatrix.append(row)

    #Hiil Climbling solution
    hcTour, hcCost = hillClimbling(n, costMatrix)
    print("Hill Climbing solution : ")
    print("Route : ", " -> ".join(map(str, hcTour)))
    print("Cost : ", hcCost)

    # Simulated Annealing Solution
    saTour, saCost = simulatedAnnealing(n, costMatrix)
    print("\nSimulated Annealing Solution : ")
    print("Route : ", " -> ".join(map(str, saTour)))

if __name__ == "__main__":
    main()