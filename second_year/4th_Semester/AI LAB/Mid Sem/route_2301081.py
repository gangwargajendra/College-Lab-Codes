import collections
import heapq
import math

# for just reading the data from text file
def readGraph(fObj):
	points = {}
	edges = collections.defaultdict(list)
	line = fObj.readline()
	numbers = line.split()
	noOfNodes = int(numbers[0])
	line = fObj.readline()
	i = 0
	while line:
		numbers = line.split()
		if len(numbers) == 2:
			firstPoint = float(numbers[0])
			scndPoint = float(numbers[1])
			points[i] = (firstPoint, scndPoint)
			i += 1
		if len(numbers) == 3:
			u = int(numbers[0])
			v = int(numbers[1])
			w = float(numbers[2])
			edges[u].append((v, w))
			edges[v].append((u, w))		
		line = fObj.readline()	
	return edges, points, noOfNodes

# it will implement UCS algorithm to find the goal point from start point
def UCS(startPoint, goalPoint, points, edges):
	start_g = 0
	minHeap = []
	heapq.heappush(minHeap, (start_g, startPoint, [startPoint]))
	visited = {startPoint: start_g}
	
	while minHeap:
		crnt_g, crnt_point, path = heapq.heappop(minHeap)
		
		# if goal is find then return path and path cost
		if crnt_point == goalPoint:
			return path, crnt_g
		
		for nei in edges[crnt_point]:
			nei_point, weight = nei
			nei_g = crnt_g + weight
			if nei_point not in visited or nei_g < visited.get(nei_point, -100):
				visited[nei_point] = nei_g
				new_path = path + [nei_point]
				heapq.heappush(minHeap, (nei_g, nei_point, new_path))
	return None, None



def main():
	fObj = open("graph_data.txt", "r")
	edges, points, noOfNodes = readGraph(fObj)
	ran = f"(0-{noOfNodes-1})" 
	startPoint = int(input(f"Enter starting point {ran}: "))
	goalPoint = int(input(f"Enter goal point {ran} : "))
	if startPoint < 0 or startPoint > 199 or goalPoint < 0 or goalPoint > 199:
		print("Not a valid input. run again....")
		return
	
	path, pathCost = UCS(startPoint, goalPoint, points, edges) 
	
	if path != None: 
		#print(f"path from {startPoint} to {goalPoint} : {path}")
		path1 = ""	
		for element in path:	
			path1 = path1 + str(element) + " -> "
		print(f"path from {startPoint} to {goalPoint} : {path1[:-3]}")
		path2 = path1[:-3]
		print(f"path cost from {startPoint} to {goalPoint}: {pathCost}")
		fObj = open("output_2301021.txt", 'w')
		fObj.write(f"path : {path2}\n pathcost : {pathCost}")
	else:
		print("Path not found.")

if __name__ == "__main__":
	main()