public class BinarySearchTree {
    BSTnode root;

    public void insert(int data){
        if(root == null){
            root = new BSTnode(data);
            return;
        }

        BSTnode curr = root;
        while (true){
           if(data < curr.data){
               if(curr.left == null){
                   curr.left = new BSTnode(data);
                   curr.left.parent = curr;
                   return;
               }
               curr = curr.left;
           } else{
               if(curr.right == null){
                   curr.right = new BSTnode(data);
                   curr.right.parent = curr;
                   return;
               }
               curr = curr.right;
           }
        }
    }


    public boolean contains(int value) {
        if (root.data == value) {
            return true;
        }
        BSTnode curr = root;
        while (curr != null){
            if (value < curr.data) {
                curr = curr.left;
            } else if (value == curr.data) {
                return true;
            } else {
                curr = curr.right;
            }
        }
        return false;
    }

    private void printInOrder(BSTnode curr){
        if(curr != null) {
            printInOrder(curr.left);
            System.out.print(curr.data);
            printInOrder(curr.right);
        }
    }

    public void inorder(){
        printInOrder(root);
    }

    public static void main(String []arr){
        BinarySearchTree b1 = new BinarySearchTree();
        b1.insert(5);
        b1.insert(3);
        b1.insert(4);
        b1.insert(7);
        b1.inorder();
        System.out.print(b1.contains(6));
    }
}
