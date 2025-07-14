import time
import heapq
import collections

def readGraph(file_object):
    edges = []
    heuristic = {}

    line = file_object.readline()
    while line:
        numbers = line.split()
        if(len(numbers) == 3):
            u = int(numbers[0])
            v = int(numbers[1])
            weight = int(numbers[2])
            edges.append((u, v, weight))
        elif (len(numbers) == 2):
            u = int(numbers[0])
            h = int(numbers[1])
            heuristic[u] = h
        line = file_object.readline()
    return edges, heuristic


def isGoal(crnt, goal=6):
    if goal == crnt:
        return True
    return False


def AStar(start, edges, heuristic, goal):
    adj = collections.defaultdict(list)
    for u, v, w in edges:
        adj[u].append((v, w))
    startTime = time.time()
    ini_h = heuristic[start]
    ini_g = 0
    ini_f = ini_h + ini_g
    minHeap = []
    heapq.heappush(minHeap, (ini_f, ini_g, start, [start]))
    visited = {start: ini_g}

    while minHeap:
        crnt_f, crnt_g, crnt_node, crnt_path = heapq.heappop(minHeap)

        if isGoal(crnt_node, goal):
            return time.time() - startTime, crnt_path, crnt_g

        if time.time() - startTime > 60:
            return None

        neighbours = adj[crnt_node]
        for neighbour in neighbours:
            nei_node, nei_w = neighbour
            nei_g = crnt_g + nei_w
            nei_h = heuristic[nei_node]
            new_path = crnt_path + [nei_node]
            if nei_node not in visited or nei_g < visited[nei_node]:
                heapq.heappush(minHeap, (nei_g + nei_h, nei_g, nei_node, new_path))
                visited[nei_node] = nei_g
    return None, None, None

def main():
    file_object = open("file_data.txt", 'r')
    edges, heuristic = readGraph(file_object)
    print(edges)
    print(heuristic)
    time, path, pathCost = AStar(1, edges, heuristic, 6)
    if path:
        print(path)
        print(pathCost)
        print(time)
    else:
        print("not found")


if __name__ == "__main__":
    main()
