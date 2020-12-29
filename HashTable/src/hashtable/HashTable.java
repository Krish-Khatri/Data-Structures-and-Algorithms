package hashtable;
import java.util.LinkedList;
import java.util.List;

public class HashTable {
    private LinkedList[]  hashtable;
    private int capacity;
    private int size;
    private int hash_code(int element){
        return element % capacity;
    }
    public HashTable(){
        this.capacity = 10;
        this.hashtable = new LinkedList[capacity];
        this.size = 0;
    }

    public HashTable(int capacity){
        this.capacity = capacity;
        this.hashtable = new LinkedList[capacity];
        this.size = 0;
    }
    public void insert(int element){
        if(hashtable[hash_code(element)] == null){
            hashtable[hash_code(element)] = new LinkedList<>();
        }

        hashtable[hash_code(element)].add(element);
        size++;
    }
    public Integer get(int element){
        List<Integer> temp_list = hashtable[hash_code(element)];
        if(temp_list != null){
            for (Integer temp : temp_list){
                if(temp.equals(element)){
                    return temp;
                }
            }
        }
        return null;
    }
    public Integer remove(int elem){
        Integer to_remove = get(elem);
        if(to_remove != null){
            hashtable[hash_code(elem)].remove(to_remove);
            size--;

            if(hashtable[hash_code(elem)].isEmpty()){
                hashtable[hash_code(elem)] = null;
            }
        }

        return to_remove;
    }

    public boolean is_empty(){
        return size == 0;
    }
    public int getSize(){
        return size;
    }
    public void print(){
        System.out.print("Hash Table: ");
        if(is_empty()) {
            System.out.print("Empty");
        } else {
            for(int i = 0; i < capacity; i++) {
                if(hashtable[i] != null) {
                    List<Integer> temp_list = hashtable[i];
                    for(Integer temp : temp_list) {
                        System.out.printf("%2d ", temp);
                    }
                } else {
                    System.out.print(" -  ");
                }
            }
        }
        System.out.print("\n");
    }
}
