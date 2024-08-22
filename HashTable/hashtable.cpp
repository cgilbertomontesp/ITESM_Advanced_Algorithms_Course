#include <iostream>
#include <vector>
#include <stdexcept>

template <typename K, typename V>
class HashTable {
public:
    HashTable(size_t initial_capacity = 8)
        : capacity(initial_capacity), size(0), load_factor(0.8) {
        table.resize(capacity, {K(), V(), false});
    }

    void insert(const K& key, const V& value) {
        if ((size + 1) > capacity * load_factor) {
            resize();
        }

        size_t index = hash(key);
        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity; // Linear probing
        }

        table[index] = {key, value, true};
        size++;
    }

    V search(const K& key) {
        size_t index = hash(key);
        size_t start_index = index;
        
        while (table[index].occupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % capacity; // Linear probing

            if (index == start_index) {
                throw std::runtime_error("Key not found");
            }
        }
        throw std::runtime_error("Key not found");
    }

    void remove(const K& key) {
        size_t index = hash(key);
        size_t start_index = index;

        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].occupied = false;
                size--;
                return;
            }
            index = (index + 1) % capacity;

            if (index == start_index) {
                throw std::runtime_error("Key not found");
            }
        }
        throw std::runtime_error("Key not found");
    }

    size_t get_size() const {
        return size;
    }

private:
    struct Entry {
        K key;
        V value;
        bool occupied = false;
    };

    std::vector<Entry> table;
    size_t capacity;
    size_t size;
    const double load_factor;

    size_t hash(const K& key) const {
        return std::hash<K>()(key) % capacity;
    }

    void resize() {
        size_t new_capacity = capacity * 2;
        std::vector<Entry> new_table(new_capacity, {K(), V(), false});

        for (const auto& entry : table) {
            if (entry.occupied) {
                size_t index = std::hash<K>()(entry.key) % new_capacity;
                while (new_table[index].occupied) {
                    index = (index + 1) % new_capacity;
                }
                new_table[index] = entry;
            }
        }

        table = std::move(new_table);
        capacity = new_capacity;
    }
};

// Example usage
int main() {
    HashTable<std::string, int> hashTable;

    hashTable.insert("key1", 1);
    hashTable.insert("key2", 2);
    hashTable.insert("key3", 3);

    std::cout << "Value for key2: " << hashTable.search("key2") << std::endl;

    hashTable.remove("key2");

    try {
        std::cout << "Value for key2: " << hashTable.search("key2") << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
\
