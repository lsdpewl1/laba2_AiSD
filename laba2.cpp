#include <iostream>
#include <vector>
#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <algorithm>

using namespace std;

class HashTable {
public:
    HashTable(size_t size, bool useDoubleHashing) : size(size), count(0), table(size, nullopt), useDoubleHashing(useDoubleHashing) {}

    void add(int key) {
        //if (2 * count >= size) {
        //    // Rehash when load factor becomes greater than 0.5
        //    rehash();  
        //}
        if (count==size) {
            //cout << "таблица заполнена" << endl;
        }
        else {

        
        size_t hash1 = hashFunc1(key);
        size_t hash2 = useDoubleHashing ? hashFunc2(key) : 1;
        while (table[hash1].has_value()) {
            hash1 = (hash1 + hash2) % size;
        }
        table[hash1] = key;
        count++;
        }
    }

    int search(int key) {
        int count = 0;
        size_t hash1 = hashFunc1(key);
        size_t hash2 = useDoubleHashing ? hashFunc2(key) : 1;
        
        /*auto it = find(table.begin(), table.end(), key);
        cout << *it << endl;*/

        while (table[hash1].has_value()) {
            //count++;
            if (table[hash1].value() == key) {
                count = 1;
                return count;
            }
            hash1 = (hash1 + hash2)  % size;
        }
        return count;
    }

    void remove(int key) {
        size_t hash1 = hashFunc1(key);
        size_t hash2 = useDoubleHashing ? hashFunc2(key) : 1;
        while (table[hash1].has_value()) {
            if (table[hash1].value() == key) {
                table[hash1] = nullopt;
                count--;
                return;
            }
            hash1 = (hash1 + hash2) % size;
        }
    }

    void print() {
        for (size_t i = 0; i < size; i++) {
            if (table[i].has_value()) {
                std::cout << i << ": " << table[i].value() << std::endl;
            }
            else {
                std::cout << i << ": " << "empty" << std::endl;
            }
        }
    }

private:
    size_t hashFunc1(int key) {
        return key % size;
    }

    size_t hashFunc2(int key) {
        // Second hash function. This must be non-zero and less than size
        return (key / size) % size + 1;
    }

    void rehash() {
        size_t newSize = 2 * size;
        std::vector<optional<int>> newTable(newSize, nullopt);
        for (size_t i = 0; i < size; i++) {
            if (table[i].has_value()) {
                size_t hash1 = table[i].value() % newSize;
                size_t hash2 = useDoubleHashing ? ((table[i].value() / newSize) % newSize) + 1 : 1;
                while (newTable[hash1].has_value()) {
                    hash1 = (hash1 + hash2) % newSize;
                }
                newTable[hash1] = table[i];
            }
        }
        table = newTable;
        size = newSize;
    }

    size_t size;
    size_t count;
    bool useDoubleHashing;
    std::vector<optional<int>> table;
};



int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");   
    int size = 10;
    HashTable ht1(size, false); // Линейное зондирование
    HashTable ht2(size, true);  // Двойное хэширование

    int a;

    int count=10;
    int av_success = 0;
    int av_unsuccess = 0;

   /* for (int i = 0; i < 100;i++) {
        a = rand();       
        ht1.add(a);      
        ht2.add(a);

    }*/

    ht1.add(5);
    ht1.add(15);

    ht2.add(5);
    ht2.add(15);

    std::cout << "Линейное зондирование:" << std::endl;
    ht1.print();
    std::cout << std::endl;

    std::cout << "Двойное хэширование:" << std::endl;
    ht2.print();
    std::cout << std::endl;

   /* for (int k = 0; k < count;k++) { 
        a = rand();     
        av_unsuccess += ht1.search(a);
        
    }*/

    //cout << "Среднее кол-во действий неуспешного поиска: " << av_unsuccess/count<<endl;

   /* ht1.add(56);
    ht1.add(32);
    ht1.add(12);
    ht1.add(35);


    ht2.add(56);
    ht2.add(32);
    ht2.add(12);
    ht2.add(35);*/


    int b;


    cin >> b;


    /*cout << "Линейное зондирование: " << ht1.search(b) << endl; 
    cout << "Двойное хэширование: " << ht2.search(b) << endl; */


    ht1.remove(b);
    ht2.remove(b);

    cin >> b;

    cout << "Линейное зондирование: " << ht1.search(b) << endl;
    cout << "Двойное хэширование: " << ht2.search(b) << endl; 


    std::cout << "Линейное зондирование:" << std::endl;
    ht1.print();
    std::cout << std::endl;

    std::cout << "Двойное хэширование:" << std::endl;
    ht2.print();
    std::cout << std::endl;

    return 0;
}
