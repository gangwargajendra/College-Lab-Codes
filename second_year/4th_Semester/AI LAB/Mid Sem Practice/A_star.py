import random
import time
import heapq

def getInitialState(gridSize):
    puzzles = []
    for _ in range(100):
        puzzle = list(range(0, gridSize*gridSize))
        random.shuffle(puzzle)
        if(isSolvable(puzzle, gridSize)):
            puzzles.append(puzzle)
        if(len(puzzles) == 10):
            break
    return puzzles


def isSolvable(puzzle, gridSize):
    inversion = 0;
    for i in range(0, gridSize*gridSize):
        for j in range(i+1, gridSize*gridSize):
            if(puzzle[i] == 0 or puzzle[j] == 0):
                continue
            if puzzle[i] > puzzle[j]:
                inversion += 1

    if gridSize % 2 != 0:
        return inversion % 2 == 0
    else:
        blankIndex = puzzle.index(0)
        blankRow = blankIndex // gridSize
        if (inversion + gridSize - blankRow) % 2 == 0:
            return True
    return False

def calHeuristic1(puzzle, gridSize):
    value = 0
    for i in range(1, gridSize*gridSize):
        index = puzzle.index(i)
        if index != i-1:
            value += 1
    return value

def calHeuristic2(puzzle, gridSize):
    value = 0
    for i in range(1, gridSize*gridSize):
        index = puzzle.index(i)
        crntRow = index // gridSize
        crntCol = index % gridSize
        goalRow = (i-1) // gridSize
        goalCol = (i-1) % gridSize
        value += abs(crntRow - goalRow) + abs(crntCol - goalCol)
    return value


def getSuccessor(puzzle, gridSize):
    neighbours = []
    zeroIndex = puzzle.index(0)
    zeroRow = zeroIndex // gridSize
    zeroCol = zeroIndex % gridSize
    if(zeroCol > 0 ):
        temp = puzzle[:]
        newZeroRow = zeroRow
        newZeroCol = zeroCol-1
        newZeroIndex = newZeroRow * gridSize + newZeroCol
        temp[zeroIndex], temp[newZeroIndex] = temp[newZeroIndex], temp[zeroIndex]
        neighbours.append(temp)
    if(zeroCol < gridSize-1):
        newZeroRow = zeroRow
        newZeroCol = zeroCol + 1
        newZeroIndex = newZeroRow * gridSize + newZeroCol
        temp1 = puzzle[:]
        temp1[zeroIndex], temp1[newZeroIndex] = temp1[newZeroIndex], temp1[zeroIndex]
        neighbours.append(temp1)
    if (zeroRow > 0):
        newZeroRow = zeroRow-1
        newZeroCol = zeroCol
        newZeroIndex = newZeroRow * gridSize + newZeroCol
        temp2 = puzzle[:]
        temp2[zeroIndex], temp2[newZeroIndex] = temp2[newZeroIndex], temp2[zeroIndex]
        neighbours.append(temp2)
    if (zeroRow < gridSize-1):
        newZeroRow = zeroRow + 1
        newZeroCol = zeroCol
        newZeroIndex = newZeroRow * gridSize + newZeroCol
        temp3 = puzzle[:]
        temp3[zeroIndex], temp3[newZeroIndex] = temp3[newZeroIndex], temp3[zeroIndex]
        neighbours.append(temp3)
    return neighbours


def isGoal(puzzle, gridSize):
    goal = list(range(1, gridSize*gridSize)) + [0]
    if goal == puzzle:
        return True
    return False


def AStar(puzzle, gridSize, startTime):
    minHeap = []
    initial_h = calHeuristic1(puzzle, gridSize)
    initial_g = 0
    initial_f = initial_h + initial_g
    heapq.heappush(minHeap, (initial_f, initial_g, puzzle))
    visited = {tuple(puzzle): initial_g}

    while minHeap:
        crnt_f, crnt_g, crnt_state = heapq.heappop(minHeap)

        if isGoal(crnt_state, gridSize):
            return time.time() - startTime

        if time.time() - startTime > 60:
            return None

        neighbours = getSuccessor(crnt_state, gridSize)
        for neighbour in neighbours:
            neighbourTuple = tuple(neighbour)
            neighbour_h = calHeuristic1(neighbour, gridSize)
            neighbour_g = crnt_g + 1
            neighbour_f = neighbour_h+ neighbour_g
            if neighbourTuple not in visited or neighbour_g < visited.get(neighbourTuple, float('inf')):
                visited[neighbourTuple] = neighbour_g
                heapq.heappush(minHeap, (neighbour_f, neighbour_g, neighbour))
    return None

def greedyBestFirstSearch(puzzle, gridSize, startTime):
    minHeap = []
    visited = set()
    initial_h = calHeuristic1(puzzle, gridSize)
    initial_f = initial_h
    heapq.heappush(minHeap, (initial_f, puzzle))
    visited.add(tuple(puzzle))

    while minHeap:
        crnt_f, crnt_state = heapq.heappop(minHeap)

        if isGoal(crnt_state, gridSize):
            return time.time() - startTime

        if time.time() - startTime > 60:
            return None

        neighbours = getSuccessor(crnt_state, gridSize)
        for neighbour in neighbours:
            neighbourTuple = tuple(neighbour)
            neighbour_h = calHeuristic1(neighbour, gridSize)
            neighbour_f = neighbour_h
            if neighbourTuple not in visited:
                visited.add(neighbourTuple)
                heapq.heappush(minHeap, (neighbour_f, neighbour))
    return None

def main():
    gridSize = int(input("Enter size of grid : "))

    puzzles = getInitialState(gridSize)
    for puzzle in puzzles:
        print(f"currently running for {puzzle}...")
        startTime = time.time()
        Atime = AStar(puzzle, gridSize, startTime)

        if Atime is not None:
            print(f"time taken to solve usning A* : {Atime:.2f}")
        else:
            print("Not solve in the given time limit in A*.")

        Gtime = greedyBestFirstSearch(puzzle, gridSize, startTime)

        if Gtime is not None:
            print(f"time taken to solve using greedy : {Gtime:.2f}")
        else:
            print("Not solve in the given time limit in Greedy .")

if __name__ == "__main__":
    main()
