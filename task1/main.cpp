/*
Реализуйте структуру данных типа “множество строк” на основе динамической  
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, 
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и 
проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.
Требования: В таблице запрещено хранение указателей на описатель элемента.
*/
#include <iostream>
#include <vector>

static const double Rehash = 1.0/3.0;

class StringHasher {
 public:
    explicit StringHasher(unsigned int prime = 137) : prime(prime) {}

    unsigned int operator()(const std::string &str) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < str.size(); i++) {
            hash = hash * prime + str[i];
        }
        return hash;
    }
 private:
    unsigned int prime;
};

template<class T, class H>
class HashTable {
 public:
    HashTable(int initialSize, const H& _hasher1, const H& _hasher2);
    ~HashTable() {
        // освобождаем память, занятую элементами таблицы
        for (auto& node : table) {
            delete[] &node;
        }
        table.clear();
    }
    bool Has(const T& key) const;

    bool Add(const T& key);

    bool Delete(const T& key);

 private:
    H hasher1;
    H hasher2;
    enum State { Empty, Key, Deleted };
    struct HashTableNode {
        T keyValue;
        State state;
        HashTableNode() : state(Empty) {}
        explicit HashTableNode(const T& key) :
            keyValue(key), state(Key) {}
    };

    std::vector<HashTableNode> table;
    unsigned int keysValue;
    unsigned int deletedKey;

    // создаем таблицу в 2 раза больше с deleted
    void growTableKeys();

    // создаем таблицу размера table.size без deleted элементов
    void growTableDeleted();
};

template<class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H& _hasher1,
                           const H& _hasher2) :
    hasher1(_hasher1),
    hasher2(_hasher2),
    table(initialSize),
    keysValue(0),
    deletedKey(0) {}

template<class T, class H>
bool HashTable<T, H>::Has(const T& key) const {
    double hash_valid = static_cast<double>(keysValue);
    unsigned int hash1 = hasher1(key);
    unsigned int hash2 = hasher2(key);
    unsigned int hashValue;
    for (unsigned int i = 0; i <= keysValue + deletedKey; i++) {
        hashValue = (hash1 + i*(2*hash2 + 1)) % table.size();

        if (table[hashValue].keyValue == key &&
          !(table[hashValue].state == Deleted)) {
            return true;
        }
        if (table[hashValue].state == Empty) {
            return false;
        }
    }
    return false;
}

template<class T, class H>
bool HashTable<T, H>::Add(const T& key) {
    double checkKeys = static_cast<double> (keysValue);
    double checkDeleted = static_cast<double> (deletedKey);
    if ((checkKeys/table.size()) >= Rehash) {
        growTableKeys();
    } else if ((checkDeleted/table.size()) >= Rehash) {
        growTableDeleted();
    }

    int deletedCheck = -1;

    unsigned int hash1 = hasher1(key);
    unsigned int hash2 = hasher2(key);
    unsigned int hashValue;

    for (unsigned int i = 0; i <= keysValue + deletedKey; i++) {
        hashValue = (hash1 + i*(2*hash2 + 1)) % table.size();

        if (table[hashValue].keyValue == key &&
            table[hashValue].state != Deleted) {
            return false;
        }

        if (table[hashValue].state == Deleted && deletedCheck < 0) {
            deletedCheck = hashValue;
        }

        if (table[hashValue].state == Empty) {
            break;
        }
    }

    if (deletedCheck < 0) {
        table[hashValue] = HashTableNode(key);
    } else {
        table[deletedCheck].keyValue = key;
        table[deletedCheck].state = Key;
        deletedKey--;
    }

    keysValue++;
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T& key) {
    double checkDeleted = static_cast<double> (deletedKey);
    if ((checkDeleted/table.size()) >= Rehash) {
        growTableDeleted();
    }

    unsigned int hash1 = hasher1(key);
    unsigned int hash2 = hasher2(key);
    unsigned int hashValue;
    for (unsigned int i = 0; i <= keysValue + deletedKey; i ++) {
        hashValue = (hash1 + i*(2*hash2 + 1)) % table.size();
        if (table[hashValue].keyValue == key &&
            table[hashValue].state != Deleted)
        {
            table[hashValue].state = Deleted;
            keysValue--;
            deletedKey++;
            return true;
        }
        if (table[hashValue].state == Empty) {
            return false;
        }
    }
    return false;
}

template<class T, class H>
void HashTable<T, H>::growTableKeys() {
    unsigned int newTableSize = table.size() * 2;
    std::vector<HashTableNode> newTable(newTableSize);
    unsigned int hash1;
    unsigned int hash2;
    unsigned int hashValue;
    for (int i = 0; i < table.size(); i++) {
        HashTableNode node = table[i];
        if (node.state != Empty) {
            hash1 = hasher1(node.keyValue);
            hash2 = hasher2(node.keyValue);
            for (int i = 0; i < newTable.size(); i++) {
                hashValue = (hash1 + i*(2*hash2 + 1)) % newTable.size();
                if (newTable[hashValue].state != Key) {
                    newTable[hashValue] = node;
                    break;
                }
            }
        }
    }
    table = newTable;
}

template<class T, class H>
void HashTable<T, H>::growTableDeleted() {
    unsigned int newTableSize = table.size();
    std::vector<HashTableNode> newTable(newTableSize);
    unsigned int hash1;
    unsigned int hash2;
    unsigned int hashValue;
    for (int i = 0; i < table.size(); i++) {
        HashTableNode node = table[i];
        if (node.state == Key) {
            hash1 = hasher1(node.keyValue);
            hash2 = hasher2(node.keyValue);
            for (int i = 0; i < newTable.size(); i++) {
                hashValue = (hash1 + i*(2*hash2 + 1)) % newTable.size();
                if (newTable[hashValue].state != Key) {
                    newTable[hashValue] = node;
                    break;
                }
            }
        }
    }
    deletedKey = 0;
    table = newTable;
    newTable.clear();
}

int main() {
    StringHasher h1(131);
    StringHasher h2(137);
    HashTable<std::string, StringHasher> table(8, h1, h2);
    char operation = 0;
    std::string word;
    while (std::cin >> operation >> word) {
        switch (operation) {
            case '+':
                std::cout << (table.Add(word)  ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Delete(word)  ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (table.Has(word) ? "OK": "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}