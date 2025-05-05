class HashNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self, size=10):
        # Initializing the hash table with a default size
        self.size = size
        self.table = [None] * size

    def _hash(self, key):
        # Hash function to calculate index based on the key
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash(key)
        new_node = HashNode(key, value)
        
        # If no collision, insert the new node at the table index
        if self.table[index] is None:
            self.table[index] = new_node
        else:
            # Collision: Chain the new node at the index
            current = self.table[index]
            while current:
                if current.key == key:
                    # Key already exists, replace the value
                    current.value = value
                    return
                if current.next is None:
                    break
                current = current.next
            # If we reach the end of the chain, add the new node
            current.next = new_node

    def find(self, key):
        index = self._hash(key)
        current = self.table[index]
        
        # Traverse the chain at the index
        while current:
            if current.key == key:
                return current.value
            current = current.next
        return None  # Key not found

    def delete(self, key):
        index = self._hash(key)
        current = self.table[index]
        prev = None
        
        # Traverse the chain to find the key
        while current:
            if current.key == key:
                if prev is None:
                    # Node to delete is the first node in the chain
                    self.table[index] = current.next
                else:
                    # Bypass the current node to delete it
                    prev.next = current.next
                return True
            prev = current
            current = current.next
        return False  # Key not found

    def display(self):
        for i in range(self.size):
            print(f"Index {i}: ", end="")
            current = self.table[i]
            while current:
                print(f"({current.key}, {current.value})", end=" -> ")
                current = current.next
            print("None")

# Usage Example
if __name__ == "__main__":
    ht = HashTable()
    ht.insert("apple", 10)
    ht.insert("banana", 20)
    ht.insert("grape", 30)
    ht.insert("apple", 50)  # Update the value for "apple"
    
    ht.display()  # Display the hash table
    
    print("\nFind 'banana':", ht.find("banana"))  # Find value for key "banana"
    print("Find 'orange':", ht.find("orange"))  # Find value for non-existent key
    
    ht.delete("grape")  # Delete key "grape"
    ht.display()  # Display the updated hash table
