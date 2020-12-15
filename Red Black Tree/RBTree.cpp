#include <iostream>
#include <memory>

using namespace std;
template <class keytype, class valuetype>
class RBTree
{
    private: 
        int nodeCount = 0;       
        enum
        {
            RED = true,
            BLACK = false,
            RIGHT = true,
            LEFT = false
        };

        class Node
        {
            public:
                Node()
                {
                    color = BLACK;
                    left = nullptr;
                    right = nullptr;
                    subTreeCount = 0;
                }

                Node(keytype k, valuetype v, int addCount)
                {
                    key = k;
                    value = v;
                    color = RED;
                    subTreeCount = addCount;
                    left = nullptr;
                    right = nullptr;
                }

                bool color;
                keytype key;
                valuetype value;
                int subTreeCount;

                std::shared_ptr<Node> left;
                std::shared_ptr<Node> right;
        };

        using nodeptr = std::shared_ptr<Node>;
        nodeptr root;
        //nodeptr array[90];
        //int count = 0;
        nodeptr copyTree(nodeptr k)
        {
            if(k == nullptr)
                return nullptr;

            nodeptr newRoot;

            newRoot = rec_insert(newRoot, k -> key, k -> value);
            newRoot -> subTreeCount = k -> subTreeCount;

            if(k -> left != nullptr){newRoot -> left = copyTree(k -> left);}
            if(k -> right != nullptr){newRoot -> right = copyTree(k -> right);}
            
            return newRoot;
        }

        int rank_of(nodeptr h, keytype key)
        {
            int rank = 0;
            while(h != nullptr)
            {
                if(key == h -> key)
                {
                    if(h -> right != nullptr)
                    {
                        rank += h->subTreeCount - h -> right ->subTreeCount;
                    }
                    else
                    {
                        rank += h->subTreeCount;
                    }
                    return rank;
                }
                else if(key < h -> key)
                {
                    h = h -> left;
                }
                else
                {
                    if(h -> right != nullptr)
                    {
                      rank += h -> subTreeCount - h -> right -> subTreeCount;  
                    }
                    else
                    {
                        rank += h -> subTreeCount;
                    }
                    h = h->right;
                }
            }
            return 0;
        }

        void gen_list_inorder(nodeptr h)
        {

            if(h == nullptr)
                return;
            gen_list_inorder(h -> left);
            std::cout << h -> key << " ";
           // array[count++] = h;
            gen_list_inorder(h -> right); 
        }

        void gen_list_postorder(nodeptr h)
        {
            if(h == nullptr)
                return;
            gen_list_postorder(h -> left);
            gen_list_postorder(h -> right);
            std::cout << h -> key << " ";
        }

        void gen_list_preorder(nodeptr h){
           // std::cout <<"in here" << std::endl;
            if(h == nullptr)
                return;
            std::cout << h -> key << " ";
            gen_list_preorder(h -> left);
            gen_list_preorder(h -> right);
        }
        keytype OSSelect(nodeptr h, int pos)
        {
            while(h != nullptr)
            {
                if(h -> right == nullptr)
                {
                    if(pos == h -> subTreeCount)
                    {
                        return h -> key;
                    }
                    else
                    {
                        h = h -> left;
                    }
                }
                else
                {
                    if(pos == (h -> subTreeCount - h -> right -> subTreeCount))
                    {
                        return h -> key;
                    }
                    else if(pos < (h -> subTreeCount - h -> right -> subTreeCount))
                    {
                        h = h -> left;
                    }
                    else
                    {
                        pos -= (h -> subTreeCount - h -> right -> subTreeCount);
                        h = h -> right;
                    }   
                } 
            }
            return 0;       
        }
        nodeptr rec_insert(nodeptr h, const keytype &key, const valuetype &value)
        {
            if(h == nullptr)
            {
                 h = std::make_shared<Node>(Node(key,value, 1));
                 return h;
            }

               // Both children are red links (4 node) -> split 4 node, passing red link up
            if (is_red(h->left) && is_red(h->right)) 
                color_flip(h);

            if (key == h->key) //Matching key, replace value
                h->value = value;       
            else if (key < h->key) 
                h->left = rec_insert(h->left, key, value);     
            else              
                h->right = rec_insert(h->right, key, value);   
            
            h -> subTreeCount++;
            // Right leaning link (3 node)  -> rotateLeft to enforce left lean
            if (is_red(h->right) && !is_red(h->left))    
                h = rotate(LEFT, h); 

            // Two consecutive red links (4 node) -> rotateRight to balance 4 node 
            if (is_red(h->left) && is_red(h->left->left)) 
                h = rotate(RIGHT, h); 
            return h;
        }

        nodeptr rec_remove(nodeptr h, const keytype &key)
        {
            if(key < h -> key)
            {
                if(!is_red(h -> left) && !is_red(h->left -> left))
                    h = move_red_left(h);
                
                h -> left = rec_remove(h -> left, key);
            }
            else
            {
                if(is_red(h -> left))
                    h = rotate(RIGHT, h);
                
                if(key == h -> key && h -> right == nullptr)
                {
                    free(h);
                    return nullptr;
                }
                if(h -> right != nullptr)
                {
                    if(!is_red(h -> right) && !is_red(h -> right -> left))
                        h = move_red_right(h);
                    
                    if(key == h -> key)
                    {
                        nodeptr temp = min_node(h -> right);
                        h -> value = temp -> value;
                        h -> key = temp -> key;

                        h -> right = rec_delete_min(h -> right);
                    }
                    else
                    {
                        h -> right = rec_remove(h-> right, key);
                    }
                    
                }
            }

            h = fixup(h);
            h -> subTreeCount--;
            return h;
        }

        nodeptr rec_delete_min(nodeptr h)
        {
            if(h -> left == nullptr)
            {
                free(h);
                return nullptr;
            }
            
            if(!is_red(h->left) && !is_red(h->left->left))
                h = move_red_left(h);
        
            h->left = rec_delete_min(h->left);

            return fixup(h);
        }

        nodeptr get(nodeptr start, const keytype &key)
        {
            if(start == nullptr)
                return nullptr;
            
            if(key == start -> key)
                return start;
            else if(key < start -> key)
                return get(start -> left, key);
            else
            {
                return get(start -> right, key);
            }
        }

        int countSubTree(nodeptr curr)
        {
            if(curr == nullptr)
                return 0;
            int i = 1 + countSubTree(curr->left) + countSubTree(curr->right);
            return i;
        }
        nodeptr rotate(bool DIRECTION, nodeptr h)
        {
            nodeptr curr;
            DIRECTION ? curr = h-> left : curr = h -> right;
            DIRECTION ? h -> left = curr -> right : h -> right = curr -> left;
            DIRECTION ? curr -> right = h : curr -> left = h;
            curr -> color = h -> color;
            h -> color = RED;
            
            curr -> subTreeCount = h -> subTreeCount;
            if(DIRECTION == false)
            {
                if(curr -> right != nullptr)
                {
                    h -> subTreeCount -= curr -> right -> subTreeCount + 1;
                }
                else
                {
                    h -> subTreeCount--;
                }
            }
            else
            {
                if(curr -> left != nullptr)
                {
                    h -> subTreeCount -= curr -> left -> subTreeCount + 1;
                }
                else
                {
                    h -> subTreeCount--;
                }
            }
            
            return curr;
        }

        nodeptr fixup(nodeptr h)
        {
            if(is_red(h -> right))
                h = rotate(LEFT,h);
            
            if(is_red(h->left) && is_red(h->left->left))
                h = rotate(RIGHT,h);
            
            if(is_red(h -> left) && is_red(h -> right))
                color_flip(h);
            
            return h;
        }

        nodeptr min_node(nodeptr h)
        {
            if( h -> left != nullptr)
            {
                h -> subTreeCount--;
                min_node(h -> left);
            } 
            return h;
        }

        nodeptr move_red_left(nodeptr h)
        {
            color_flip(h);
            if(is_red(h -> right -> left))
            {
                h -> right = rotate(RIGHT, h -> right);
                h = rotate(LEFT, h);
                color_flip(h);
            }
            return h;
        }

        nodeptr move_red_right(nodeptr h)
        {
            color_flip(h);
            if(is_red(h -> left -> left))
            {
                h = rotate(RIGHT, h);
                color_flip(h);
            }
            return h;
        }

        void color_flip(nodeptr h)
        {
            h -> color = !h->color;
            h -> left -> color = !h -> left -> color;
            h -> right -> color = !h -> right -> color;
        }

        bool is_red(const nodeptr m)
        {
            if(m == nullptr)
                return false;
            return m -> color;
        }

        void free(nodeptr root)
        {
            if(root != nullptr)
            {
                free(root -> left);
                free(root -> right);
                root.reset();
            }
        }
        void setChild(nodeptr node, bool toLeft, nodeptr child)
        {
            if(toLeft)
            {
                node -> left = child;
            }
            else
            {
                node -> right = child;
            }
            
        }
        void fixSubTreeCount(nodeptr h)
        {
            h -> subTreeCount = countSubTree(h);

            if(h -> left != nullptr){h -> subTreeCount = countSubTree(h);}
            if(h -> right != nullptr){h -> subTreeCount = countSubTree(h);}
        }
        nodeptr splitHelper(keytype k, nodeptr root1)
        {
            nodeptr root2 =  nullptr;
            nodeptr parent1 = nullptr;
            nodeptr parent2 = nullptr;

            bool toLeft = root1 != nullptr && k < root1 -> key;
            while(root1 != nullptr)
            {
                while(root1 != nullptr && (k < root1 -> key) == toLeft)
                {
                    parent1 = root1;
                    root1 = toLeft ? root1 -> left : root1 -> right;
                }
                setChild(parent1, toLeft, nullptr);
                toLeft = !toLeft;
                if(root2 == nullptr)
                    root2 = root1;
                else if(parent2 != nullptr)
                {
                    setChild(parent2,toLeft,root1);
                }          
                parent2 = parent1;
                parent1 = nullptr; 
            }
            return root2; 
        }

    public:
        RBTree();
        RBTree(keytype k[], valuetype v[], int s);
        RBTree(const RBTree &copyFrom);
        RBTree &operator=(const RBTree &copyFrom);
        ~RBTree();
        valuetype * search(keytype k);
        void insert(keytype k, valuetype v);
        int remove(keytype k);
        int rank(keytype k);
        keytype select(int pos);
        void split(keytype k, RBTree<keytype,valuetype> &T1, RBTree<keytype,valuetype> &T2);
        int size();
        void preorder();
        void inorder();
        void postorder();
};

// Default Constructor
template <class keytype, class valuetype>
RBTree<keytype,valuetype>::RBTree()
{
    root = nullptr;
    nodeCount = 0;
}

// Constructor Overload ** Custom Constructor **
template <class keytype, class valuetype>
RBTree<keytype,valuetype>::RBTree(keytype k[], valuetype v[], int s)
{
    nodeCount = 0;
    for(int i = 0; i < s; i++)
    {
        insert(k[i], v[i]);
    }
}

//Copy Constructor
template <class keytype, class valuetype>
RBTree<keytype,valuetype>::RBTree(const RBTree &copyFrom)
{
    this -> root = copyTree(copyFrom.root);
    this -> nodeCount = copyFrom.nodeCount;
}

//Copy Assignment Operator
template <class keytype, class valuetype>
RBTree<keytype,valuetype>& RBTree<keytype,valuetype>::operator=(const RBTree &copyFrom)
{
    if(this != &copyFrom)
    {
        free(this -> root);
        RBTree temp(copyFrom);
        std::swap(temp.root,this -> root);
        this -> nodeCount = copyFrom.nodeCount;
    }
    return *this;
}
//Destructor
template <class keytype, class valuetype>
RBTree<keytype,valuetype>::~RBTree()
{
    free(root);
    root = nullptr;
}

//Search Function: Search for a key in the tree. Return Associated pointer to the value of the key if found
template <class keytype, class valuetype>
valuetype* RBTree<keytype,valuetype>::search(keytype k)
{
    nodeptr node = get(root,k);
    if(node == nullptr)
        return NULL;
    else
    {
        valuetype *returntype = &node -> value;
        return returntype;
    }
    return NULL;    
}

//Inserts an element into the tree
template <class keytype, class valuetype>
void RBTree<keytype,valuetype>::insert(keytype key, valuetype value)
{
    nodeCount++;
    root = rec_insert(root, key, value);
    root -> color = BLACK;
}

//Delete a key in the tree
template <class keytype, class valuetype>
int RBTree<keytype,valuetype>::remove(keytype key)
{
    valuetype *found = search(key);
    if(found != NULL)
    {
        if(root != nullptr)
        {
            nodeCount--;
            root = rec_remove(root,key);
            if(root != nullptr)
                root -> color = BLACK;
        }
        return 1;
    }
    return 0;
}

template <class keytype, class valuetype>
int RBTree<keytype,valuetype>::rank(keytype k)
{
    int rank = rank_of(root, k);
    return rank;
}

template <class keytype, class valuetype>
keytype RBTree<keytype,valuetype>::select(int pos)
{
    keytype value = OSSelect(root, pos);
    return value;
}

template <class keytype, class valuetype>
void RBTree<keytype,valuetype>::split(keytype k, RBTree<keytype,valuetype> &T1, RBTree<keytype,valuetype> &T2)
{
    T2.root = splitHelper( k, root);
    fixSubTreeCount(root);
    fixSubTreeCount(T2.root);
    T1.root = root;
}

template <class keytype, class valuetype>
int RBTree<keytype,valuetype>::size()
{
    return nodeCount;
}

template <class keytype, class valuetype>
void RBTree<keytype,valuetype>::preorder()
{
    gen_list_preorder(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype,valuetype>::inorder()
{
    gen_list_inorder(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype,valuetype>::postorder()
{
    gen_list_postorder(root);
    cout << endl;
}

