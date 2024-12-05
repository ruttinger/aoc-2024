from collections import defaultdict, deque, Counter

def check_in_degrees(in_degree):
    zero_in_degree_nodes = [node for node in in_degree if in_degree[node] == 0]
    print("Nodes with in-degree 0:", zero_in_degree_nodes)
    return zero_in_degree_nodes

def topological_sort(precedence_rules):
    graph = defaultdict(list)
    in_degree = defaultdict(int)
    nodes = set()  # To keep track of all nodes
    
    # Build the graph and in_degree map
    for a, b in precedence_rules:
        graph[a].append(b)
        in_degree[b] += 1
        if a not in in_degree:
            in_degree[a] = 0  # Add nodes with 0 in-degree
    
        nodes.add(a)
        nodes.add(b)
    
    # print("Graph:", graph)
    # print("In-degree map:", in_degree)

    print(check_in_degrees(in_degree))
    
    # Initialize queue with nodes that have 0 in-degree
    queue = deque([node for node in nodes if in_degree[node] == 0])
    # print("Initial queue:", queue)

    topological_order = []
    
    while queue:
        current = queue.popleft()
        topological_order.append(current)
        
        # Decrease the in-degree of neighbors
        for neighbor in graph[current]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    # Check if topological sort is possible (i.e., no cycle)
    if len(topological_order) != len(nodes):
        raise ValueError("The precedence rules contain a cycle!")
    
    return topological_order

def order_numbers(precedence_rules):
    # Step 1: Build the graph and compute in-degrees
    graph = defaultdict(list)
    in_degree = defaultdict(int)
    nodes = set()  # To keep track of all nodes
    
    for a, b in precedence_rules:
        graph[a].append(b)
        in_degree[b] += 1
        if a not in in_degree:
            in_degree[a] = 0
        
        nodes.add(a)
        nodes.add(b)

    # Step 2: Perform topological sort using Kahn's algorithm
    queue = deque([node for node in nodes if in_degree[node] == 0])
    ordered_numbers = []

    while queue:
        current = queue.popleft()
        ordered_numbers.append(current)
        
        for neighbor in graph[current]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    # Check for cycles (if all nodes are not included, there's a cycle)
    if len(ordered_numbers) != len(in_degree):
        raise ValueError("The precedence rules contain a cycle!")

    return ordered_numbers

def relative_sort(values, precedence_order):
    precedence_map = {value: i for i, value in enumerate(precedence_order)}
    return sorted(values, key=lambda x: precedence_map.get(x, float('inf')))

def main():
    precedence_rules = []
    precedence_order = []
    values = []

    totalPageNum = 0

    with open("example.txt", "r") as file:
        for line in file:
            if line in ['\n', '\r\n']:
                # precedence_order = topological_sort_with_dfs(precedence_rules)
                precedence_order = topological_sort(precedence_rules)
            elif '|' in line:
                line = line.strip()
                value1, value2 = line.split('|')
                value1, value2 = int(value1), int(value2)
                precedence_rules.append((value1, value2))
            elif ',' in line:
                values = [int(v) for v in line.split(',')]
                print(relative_sort(values, precedence_order))
                print(values)
                if relative_sort(values, precedence_order) == values:
                    # print('sorted correctly', values)
                    totalPageNum += values[int((len(values)-1)/2)]

    print(totalPageNum)


if __name__ == "__main__":
    main()

