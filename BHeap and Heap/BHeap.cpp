#include <iostream>
#include <stack>

using namespace std;
template <class keytype,class valuetype>
class BHeap{
    struct Node{
        keytype key;
        valuetype value;
        int degree;
        Node *parent, *child, *sibling;
    };

private:
    //Make root global
    Node *root = nullptr;

    // Creates a Node
    Node *init_Node(keytype k , valuetype v){
        Node *new_Node = new Node;
        new_Node -> key = k;
        new_Node -> value = v;
        new_Node -> degree = 0;
        new_Node -> child = new_Node -> sibling = new_Node -> parent = nullptr;
        return  new_Node;
    }

    // Link 2 Trees, H2 is the parent and H1 is the child
    void linkTrees(Node *h1, Node *h2){
        h1 -> parent = h2;
        h1 -> sibling = h2 -> child;
        h2 -> child = h1;
        h2 -> degree++;
    }
    // Function merges two trees
    Node *mergeHeaps(Node *h1, Node *h2){
        Node *groot = nullptr;
        Node **pos = &groot;

        // if h1 is null, set h2 as head or vice versa
        if(h1 == nullptr){
            return h2;
        } else if (h2 == nullptr){
            return h1;
        }

        //Traverse till any one of two heaps is empty
        while (h1 && h2){
            //Check degree of both node ie. which is greater or smaller
            if(h1 -> degree < h2 -> degree){
                *pos = h1;
                h1 = h1 -> sibling;
            } else {
                *pos = h2;
                h2 = h2 -> sibling;
            }
            pos = &(*pos) -> sibling;
        }

        // Final adjustments
        if(h1)
            *pos = h1;
        else
            *pos = h2;

        return  groot;

//
//        Node *res = nullptr;
//        if(h1 -> degree <= h2 -> degree)
//            res = h1;
//        else if(h1 -> degree > h2 -> degree)
//            res = h2;
//
//        while (h1 != nullptr && h2 != nullptr){
//            if(h1 -> degree < h2 -> degree)
//                h1 = h1 -> sibling;
//            else if(h1 -> degree == h2 -> degree){
//                Node *sib = h1 -> sibling;
//                h1 -> sibling = h2;
//                h1 = sib;
//            } else {
//                Node *sib = h2 -> sibling;
//                h2 -> sibling = h1;
//                h2 = sib;
//            }
//        }
//        return  res;
    }
    // This function performs union operation on two binomial heaps (They are technically 2 tree nodes)
    Node *unionBHeaps(Node *h1, Node *h2){
        if(h1 == nullptr && h2 == nullptr)
            return nullptr;
        Node *res = mergeHeaps(h1,h2);

        //Traverse the merged list and set values according to the degree of nodes
        Node *prev = nullptr , *curr = res, *next = curr -> sibling;
        while (next != nullptr){
            if((curr -> degree != next -> degree) || ((next -> sibling != nullptr) && ((next -> sibling) -> degree == curr -> degree))){
                prev = curr;
                curr = next;
            } else {
                if(curr -> key <= next -> key){
                    curr -> sibling = next -> sibling;
                    // set next as child of curr
                    linkTrees(next,curr);
                } else {
                    if(prev == nullptr)
                        res = next;
                    else
                        prev -> sibling = next;
                    // set next as parent of curr
                    linkTrees(curr,next);
                    curr = next;
                }
            }
            next = curr -> sibling;
        }
        return res;
    }
// This function reverses the rest of the node using recursion but for some reason this broke extract min :)
//    void revertList(Node *h){
//        if(h -> sibling != nullptr)
//        {
//            revertList(h -> sibling);
//            (h -> sibling) -> sibling = h;
//        }
//        else
//            root = h;
//    }

    // Displays the heap
    void display(Node *h){
        while (h)
        {
            if(!h -> parent)
            {
                cout << endl << "B" << h -> degree << endl;
            }
            cout << h->key << " ";
            display(h->child);
            h = h->sibling;
        }
    }

    // Function to extract minimum value
    Node *extractMinBHeap(Node *h){
        Node *curr = root;
        Node *prevMin = nullptr;
        Node *minPtr = nullptr;
        Node *prevPtr = nullptr;
        keytype min = root -> key;

        // Finds the minimum value
        while (curr != nullptr){
            if(curr -> key <= min){
                min = curr -> key;
                prevMin = prevPtr;
                minPtr = curr;
            }
            prevPtr = curr;
            curr = curr -> sibling;
        }

        // If there is a single node you can do this.
        if (prevMin != nullptr && minPtr->sibling != nullptr) {
            prevMin->sibling = minPtr->sibling;
        } else if (prevMin != nullptr && minPtr->sibling == nullptr) {
            prevMin->sibling = nullptr;
        }

        Node *childPtr = minPtr -> child;
        while (childPtr != nullptr) {
            childPtr->parent = nullptr;
            childPtr = childPtr->sibling;
        }
        // Use a stack to reverse the list. IDK the function doesnt work, but this works.
        // Anyways you iterate through the rest of the heap and just push it to the stack.
        // Its Last in first out obv.
        stack<Node*> s;
        childPtr = minPtr->child;
        while (childPtr != nullptr) {
            s.push(childPtr);
            childPtr = childPtr->sibling;
        }

        curr = s.top();
        Node* temp = curr;
        s.pop();
        // Set root as children of the mind node list
        while (!s.empty()) {
            curr->sibling = s.top();
            s.pop();
            curr = curr->sibling;
        }

        curr->sibling = nullptr;
        // Do union of root and children
        root = unionBHeaps(root,temp);
        return root;
//        if(h == nullptr)
//            return nullptr;
//        Node *min_node_prev = nullptr;
//        Node *min_node = h;
//
//        keytype min = h -> key;
//        Node *curr = h;
//        while (curr -> sibling != nullptr){
//            if ((curr -> sibling) -> key < min){
//                min = curr -> sibling -> key;
//                min_node_prev = curr;
//                min_node = curr -> sibling;
//            }
//            curr = curr -> sibling;
//        }
//
//        if(min_node_prev == nullptr && min_node -> sibling == nullptr)
//            h = nullptr;
//        else if(min_node_prev == nullptr)
//            h = min_node -> sibling;
//        else
//            min_node_prev -> sibling = min_node -> sibling;
//
//        if(min_node -> child != nullptr){
//            revertList(min_node -> child);
//            (min_node -> child) -> sibling = nullptr;
//        }
//        return unionBHeaps(h,root);
    }
public:
    // Default Constructor
    BHeap(){
        root = nullptr;
    }
    // Secondary Constructor. This needs to be O(s). but im not sure it is
    BHeap(keytype k[], valuetype v[], int s){
        for(int i = 0; i < s; i++){
            insert(k[i],v[i]);
        }
    }
    // Destructor
    ~BHeap(){
        delete root;
        root = nullptr;
    }
    // Insert Function.
    // Creates a new node that has keytype k and valuetype v as it's data and
    // performs a union on the 2 heaps (Trees)
    void insert(keytype k, valuetype v){
        root = unionBHeaps(root, init_Node(k,v));
    }
    // Iterates through the tree and returns the min key
    // Should create a function that just finds the min
    // because code is redundant.
    keytype peakKey(){
        // Node *min_node_prev = nullptr;
        Node *min_node = root;
        keytype min = root -> key;
        Node *curr = root;
        while (curr -> sibling != nullptr){
            if ((curr -> sibling) -> key < min){
                min = curr -> sibling -> key;
                //min_node_prev = curr;
                min_node = curr -> sibling;
            }
            curr = curr -> sibling;
        }
        return min_node -> key;
    }
    // Iterates through the tree and returns the min value
    valuetype peakValue(){
        //Node *min_node_prev = nullptr;
        Node *min_node = root;
        keytype min = root -> key;
        Node *curr = root;
        while (curr -> sibling != nullptr){
            if ((curr -> sibling) -> key < min){
                min = curr -> sibling -> key;
                // min_node_prev = curr;
                min_node = curr -> sibling;
            }
            curr = curr -> sibling;
        }
        return min_node -> value;
    }
    // Extract Min function.
    // Should just return min key through extractMin Function
    // but i decided to be difficult
    keytype extractMin(){
        keytype min = peakKey();
        root = extractMinBHeap(root);
        return min;
    }
    // Merges two heaps
    void merge(BHeap<keytype,valuetype> &h2){
        Node *secondRoot =  h2 . root;
        root = unionBHeaps(root , secondRoot);
    }
    // Print all keys in the heap
    void printKey(){
        display(root);
        cout << endl;
    }
};


