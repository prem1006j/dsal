# Hash Table Implementation with Separate Chaining
class HashTableSeparateChaining:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]
    
    def hash(self, key):
        return hash(key) % self.size
    
    def insert(self, key, value):
        index = self.hash(key)
        self.table[index].append((key, value))
    
    def find(self, key):
        index = self.hash(key)
        comparisons = 0
        for item in self.table[index]:
            comparisons += 1
            if item[0] == key:
                return item[1], comparisons
        return None, comparisons

# Hash Table Implementation with Linear Probing (Open Addressing)
class HashTableLinearProbing:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
    
    def hash(self, key):
        return hash(key) % self.size
    
    def insert(self, key, value):
        index = self.hash(key)
        while self.table[index] is not None:
            index = (index + 1) % self.size
        self.table[index] = (key, value)
    
    def find(self, key):
        index = self.hash(key)
        comparisons = 0
        while self.table[index] is not None:
            comparisons += 1
            if self.table[index][0] == key:
                return self.table[index][1], comparisons
            index = (index + 1) % self.size
        return None, comparisons

# Test the two hash table implementations
def test_collision_handling():
    # Initialize two hash tables with the same size
    size = 10
    hash_table_chaining = HashTableSeparateChaining(size)
    hash_table_linear = HashTableLinearProbing(size)
    
    # Insert some clients into both hash tables
    clients = [
        ("Ram", "555-1234"),
        ("sita", "555-2345"),
        ("radha", "555-3456"),
        ("Kartiki", "555-4567"),
        ("nita", "555-5678"),
    ]
    
    for name, number in clients:
        hash_table_chaining.insert(name, number)
        hash_table_linear.insert(name, number)
    
    # Search for telephone numbers and count comparisons
    search_names = ["Ram", "sita", "radha"]
    
    print("Separate Chaining Results:")
    for name in search_names:
        number, comparisons = hash_table_chaining.find(name)
        print(f"Found {name}'s number: {number}, Comparisons: {comparisons}")
    
    print("\nLinear Probing Results:")
    for name in search_names:
        number, comparisons = hash_table_linear.find(name)
        print(f"Found {name}'s number: {number}, Comparisons: {comparisons}")

# Run the test
test_collision_handling()
