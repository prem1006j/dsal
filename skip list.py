import random

class Node:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.level = 0
        self.header = Node(None, self.max_level)
    
    def random_level(self):
        level = 0
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level
    
    def insert(self, value):
        update = [None] * (self.max_level + 1)
        current = self.header
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current
        
        new_level = self.random_level()
        if new_level > self.level:
            for i in range(self.level + 1, new_level + 1):
                update[i] = self.header
            self.level = new_level
        
        new_node = Node(value, new_level)
        for i in range(new_level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node
    
    def search(self, value):
        current = self.header
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
        current = current.forward[0]
        if current and current.value == value:
            return current.value
        return None
    
    def find_closest(self, value):
        current = self.header
        closest_value = None
        min_diff = float('inf')
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            if current.forward[i]:
                diff = abs(current.forward[i].value - value)
                if diff < min_diff:
                    min_diff = diff
                    closest_value = current.forward[i].value
        return closest_value

    def display(self):
        for i in range(self.level + 1):
            current = self.header.forward[i]
            print(f"Level {i}: ", end="")
            while current:
                print(current.value, end=" -> ")
                current = current.forward[i]
            print("None")

if __name__ == "__main__":
    skiplist = SkipList(max_level=4)
    
    elements = [3, 6, 7, 9, 12, 17, 19, 21, 25, 30]
    for elem in elements:
        skiplist.insert(elem)
    
    skiplist.display()
    
    print(f"\nSearch for 17: {skiplist.search(17)}")
    print(f"Search for 20: {skiplist.search(20)}")
     
    value = 16
    closest = skiplist.find_closest(value)
    print(f"\nClosest element to {value}: {closest}")
