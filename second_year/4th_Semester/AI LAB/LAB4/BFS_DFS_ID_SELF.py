import time
import random
import statistics
from collections import deque
import matplotlib.pyplot as plt


def createRandomPuzzle(gridSize):
    puzzles = []
    for _ in range(10):
        puzzle = list(range(1, gridSize*gridSize)) + [0]
        random.shuffle(puzzle)
        puzzles.append(puzzle)
    return puzzles

def swap(list, i, j):
    list[i], list[j] = list[j], list[i]

def getNeighbours(puzzle, gridSize):
    neighbours = []
    zeroIndex = puzzle.index(0)
    row = zeroIndex // gridSize
    col = zeroIndex % gridSize

    # move up
    if row != 0:
        tempPuzzle = puzzle[:]
        oneIndex = (row-1) * gridSize + col
        swap(tempPuzzle, oneIndex, zeroIndex)
        neighbours.append(tempPuzzle)
    # down
    if row != gridSize-1:
        tempPuzzle = puzzle[:]
        oneIndex = (row+1) * gridSize + col
        swap(tempPuzzle, oneIndex, zeroIndex)
        neighbours.append(tempPuzzle)
    # left
    if col != 0:
        tempPuzzle = puzzle[:]
        oneIndex = row * gridSize + (col - 1)
        swap(tempPuzzle, oneIndex, zeroIndex)
        neighbours.append(tempPuzzle)
    # right
    if col != gridSize-1:
        tempPuzzle = puzzle[:]
        oneIndex = row * gridSize + (col+1)
        swap(tempPuzzle, oneIndex, zeroIndex)
        neighbours.append(tempPuzzle)
    return neighbours

def isGoal(puzzle, gridSize):
    gaolPuzzle = list(range(1, gridSize*gridSize)) + [0]
    return gaolPuzzle == puzzle

def BFS(startState, gridSize):
    startTime = time.time()
    visited = set()
    queue = deque([startState])
    visited.add(tuple(startState))

    while queue:
        currentState = queue.popleft()

        if isGoal(currentState, gridSize):
            return time.time() - startTime

        neighbours = getNeighbours(currentState, gridSize)
        for neighbour in neighbours:
            neighbourTuple = tuple(neighbour)
            if neighbourTuple not in visited:
                queue.append(neighbour)
                visited.add(neighbourTuple)

        if time.time() - startTime > 60:
            return None

def DFS(startState, gridSize):
    startTime = time.time()
    visited = set()
    stack = [(startState, 0)]
    visited.add(tuple(startState))

    while stack:
        currentState, steps = stack.pop()

        if isGoal(currentState, gridSize):
            return time.time() - startTime

        neighbours = getNeighbours(currentState, gridSize)
        for neighbour in reversed(neighbours):
            neighbourTuple = tuple(neighbour)
            if neighbourTuple not in visited:
                visited.add(neighbourTuple)
                stack.append((neighbour, steps+1))

        if(time.time() - startTime > 60):
            return None
    return None

def depthlimitSearch(startState, gridSize, depth, startTime):
    visited = set()
    stack = [(startState, 0)]
    visited.add(tuple(startState))

    while stack:
        crntState, steps = stack.pop()

        if isGoal(crntState, gridSize):
            return time.time() - startTime

        neighbours = getNeighbours(crntState, gridSize)

        for neighbour in reversed(neighbours):
            neighbourTuple = tuple(neighbour)
            if depth > steps and neighbourTuple not in visited:
                visited.add(neighbourTuple)
                stack.append((neighbour, steps+1))

        if time.time()-startTime > 60:
            return None

    return None

def ID(startState, gridSize):
    startTime = time.time()
    depth = 0

    while True:
        result = depthlimitSearch(startState, gridSize, depth, startTime)
        if result is not None:
            return result
        if time.time() - startTime > 60:
            return None
        depth += 1


def main():
    gridSize = int(input("Enter the size of puzzle : "))
    algorithmsTime = {
        'BFS': [],
        'DFS': [],
        'ID': [],
    }

    puzzles = createRandomPuzzle(gridSize)
    for puzzle in puzzles :
        print(f"for puzzle : {puzzle}")
        BFSTime = BFS(puzzle, gridSize)
        if BFSTime is not None :
            print(f"time taken to solve this puzzle using BFS : {BFSTime:.2f}\n")
            algorithmsTime['BFS'].append(BFSTime)
        else:
            print("Not solve in given time using BFS.")

        DFSTime = DFS(puzzle, gridSize)
        if DFSTime is not None :
            print(f"time taken to solve this puzzle using DFS : {DFSTime:.2f}\n")
            algorithmsTime['DFS'].append(DFSTime)
        else:
            print("Not solve in given time using DFS.")

        IDTime = ID(puzzle, gridSize)
        if IDTime is not None:
            print(f"time taken to solve this puzzle using ID : {IDTime:.2f}\n")
            algorithmsTime['ID'].append(IDTime)
        else:
            print("Not solve in given time using ID.")

    avgTimeAlgo = {}

    avgTimeAlgo['BFS'] = statistics.mean(algorithmsTime['BFS'])
    avgTimeAlgo['DFS'] = statistics.mean(algorithmsTime['DFS'])
    avgTimeAlgo['ID'] = statistics.mean(algorithmsTime['ID'])

    algorithms = list(avgTimeAlgo.keys())
    avgTime = list(avgTimeAlgo.values())

    plt.bar(algorithms, avgTime)
    plt.xlabel("algorithms")
    plt.ylabel("avg. time(sec)")
    plt.title("AI algorithms")
    plt.show()


if __name__ == "__main__":
    main()