from collections import deque

def get_new(five_jug, three_jug):
    new_combinations = []
    actions = {"Fill the 5-liter jug completely.",
               "Fill the 3-liter jug completely.",
               "Empty the 5-liter jug.",
               "Empty the 3-liter jug.",
               "Pour water from the 5-liter jug into the 3-liter jug until the 3-liter jug is full or the 5-liter jug is empty.",
               "Pour water from the 3-liter jug into the 5-liter jug until the 5-liter jug is full or the 3-liter jug is empty."
               }

    if five_jug != 5:
        new_combinations.append((5, three_jug))

    if three_jug != 3:
        new_combinations.append((five_jug, 3))

    if five_jug != 0:
        new_combinations.append((0, three_jug))

    if three_jug != 0:
        new_combinations.append((five_jug, 0))

    if five_jug != 0 and three_jug != 3:
        max_pour_water = 3 - three_jug
        if max_pour_water <= five_jug:
            new_combinations.append((five_jug - max_pour_water, three_jug + max_pour_water))
        else:
            new_combinations.append((0, three_jug + five_jug))

    if three_jug != 0 and five_jug != 5:
        max_pour_water = 5 - five_jug
        if max_pour_water <= three_jug:
            new_combinations.append((five_jug + max_pour_water, three_jug - max_pour_water))
        else:
            new_combinations.append((5, three_jug - (5 - five_jug)))

    return new_combinations


def bfs(five_jug, three_jug):
    visited = set()
    queue = deque([(five_jug, three_jug, 0, [])])
    visited.add((five_jug, three_jug))

    while queue:
        current_five, current_three, current_step, current_path = queue.popleft()

        if current_five == 4:
            return current_step, current_path + [(current_five, current_three)]

        for com in get_new(current_five, current_three):
            new_five, new_three = com
            new_com = (new_five, new_three)

            if new_com not in visited:
                visited.add(new_com)
                queue.append((new_five, new_three, current_step + 1, current_path + [(current_five, current_three)]))

    return -1, []



steps, path = bfs(0, 0)

print(f"Steps to find result: {steps}")
print("Path:")
for step in path:
    print(step)
