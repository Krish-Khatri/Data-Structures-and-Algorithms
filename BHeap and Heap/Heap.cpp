#include <iostream>
#include <algorithm>

using namespace std;
template <class keytype, class valuetype>
class Heap{
    struct heapItem{
        keytype key;
        valuetype value;
    };

private:
    heapItem *arr;
    int capacity;
    int size;

    void doubleCap(){
        if(this -> arr == nullptr){
            this -> arr = new heapItem[1];
            this -> capacity = 1;
            return;
        }

        int newCap = capacity * 2;
        heapItem *newArr = new heapItem[newCap];

        for (int i = 0; i < this -> size; i++){
            newArr[i] = this -> arr[i];
        }
        if(this -> arr != nullptr)
            delete this -> arr;

        this -> capacity = newCap;
        this -> arr = newArr;
    }

    void shiftUp(int index){
        if(index < 1)
            return;

        int parent = (index - 1) / 2;

        if(this -> arr[index].key < this -> arr[parent].key)
            swap(this -> arr[index], this -> arr[parent]);

        shiftUp(parent);
    }

    void shiftDown(int index){
        int minIndex = -1;
        int lChild = index * 2 + 1;
        int rChild = index * 2 + 2;

        if(lChild < size){
            if(arr[index].key > arr[lChild].key){
                minIndex = lChild;
            }
        }

        if(rChild < size){
            if(arr[(minIndex == -1 ? index : minIndex)].key > arr[rChild].key){
                minIndex = rChild;
            }
        }

        if(minIndex == -1)
            return;

        swap(arr[index], arr[minIndex]);
        shiftDown(minIndex);
    }

    void reduceCap(){
        int newCap = capacity / 2;
        heapItem *newArr = new heapItem[newCap];

        for (int i = 0; i < this -> size; i++){
            newArr[i] = this -> arr[i];
        }
        if(this -> arr != nullptr)
            delete this -> arr;

        this -> capacity = newCap;
        this -> arr = newArr;
    }


public:
    Heap(){
        this -> arr = nullptr;
        this -> capacity = 0;
        this -> size = 0;
    }

    Heap(keytype k[], valuetype v[], int s){
        this -> arr = new heapItem[s];
        this -> size = 0;
        this -> capacity = s;

        for(int i = 0; i < capacity; i++){
            arr[i].key = k[i];
            arr[i].value = v[i];
            this -> size++;
        }

        for(int i = this -> size - 1; i >= 0; --i){
            shiftDown(i);
        }
    }
    Heap(const Heap &a){
        arr = new heapItem[a.capacity];
        for(int i = 0; i < a.size; i++){
            arr[i].key = a.arr[i].key;
            arr[i].value = a.arr[i].value;
        }
        this -> size = a.size;
        this -> capacity = a.capacity;
    }
    Heap &operator=(const Heap &a){
        if(this == &a)
            return *this;

        arr = new heapItem[a.capacity];
        for(int i = 0; i < a.size; i++){
            arr[i].key = a.arr[i].key;
            arr[i].value = a.arr[i].value;
        }
        this -> size = a.size;
        this -> capacity = a.capacity;
        return *this;
    }
    ~Heap(){
        if(this -> arr != nullptr){
            delete[](arr);
            arr = nullptr;
            this -> capacity = 0;
            this -> size = 0;
        }
    }

    keytype peakKey(){
        return arr[0].key;
    }

    valuetype peakValue(){
        return arr[0].value;
    }

    keytype extractMin(){
        keytype minKey = arr[0].key;
        swap(arr[0], arr[this -> size - 1]);
        size --;
        if(size <= capacity / 4){
            reduceCap();
        }
        shiftDown(0);

        return minKey;
    }

    void insert(keytype k, valuetype v){
        if(this -> size == this -> capacity){
            doubleCap();
        }

        this -> arr[size].key = k;
        this -> arr[size].value = v;

        shiftUp(size);
        this -> size++;
    }

    void printKey(){
        for(int i = 0; i < this -> size; i++){
            cout << arr[i].key << " ";
        }
        cout << endl;
    }
};