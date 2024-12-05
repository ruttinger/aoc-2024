
from collections import defaultdict, deque

def validate_order(values, graph):
    last_node = None
    is_correct = True
    for value in values:
        if last_node is None:
            last_node = value
        elif last_node in graph and value in graph[last_node]:
            last_node = value
        else:
            is_correct = False
            break
    return is_correct

def order_values(values, graph):
    last_node = None
    is_correct = True
    for value in values:
        if last_node is None:
            last_node = value
        elif last_node in graph and value in graph[last_node]:
            last_node = value
        else:
            is_correct = False
            index = values.index(value)
            if index > 0:
                values.pop(index)
                values.insert(index - 1, value)
            is_ordered, values = order_values(values, graph)
            if is_ordered:
                return is_correct, values
    return is_correct, values

def main():
    precedence_rules = []
    totalPageNum = 0
    totalOrderedPageNum = 0

    graph = defaultdict(list)

    with open("input.txt", "r") as file:
        for line in file:
            if line in ['\n', '\r\n']:
                for a, b in precedence_rules:
                    graph[a].append(b)
                print(graph)
            elif '|' in line:
                line = line.strip()
                value1, value2 = line.split('|')
                value1, value2 = int(value1), int(value2)
                precedence_rules.append((value1, value2))
            elif ',' in line:
                values = [int(v) for v in line.split(',')]
                if validate_order(values, graph):
                    totalPageNum += values[int((len(values)-1)/2)]
                else:
                    _, ordered_values = order_values(values, graph)
                    totalOrderedPageNum += ordered_values[int((len(ordered_values)-1)/2)]

    print(totalPageNum)
    print(totalOrderedPageNum)

if __name__ == "__main__":
    main()
