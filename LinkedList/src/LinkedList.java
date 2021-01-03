public class LinkedList {
    Node head;

    public void append(int data){
        if(head == null){
            head = new Node(data);
            return;
        }

        Node curr = head;
        while(curr.next != null){
            curr = curr.next;
        }
        curr.next = new Node(data);
    }

    public void delete(int data){
        if(head.data == data){
            head = head.next;
            return;
        }

        Node curr = head;
        while (curr.next != null){
            if(curr.next.data == data){
                curr.next = curr.next.next;
            }
            curr = curr.next;
        }
    }

    public void print(){
        Node curr = head;
        while (curr != null){
            System.out.print(curr.data + " -> ");
            curr = curr.next;
        }
    }

    public static void main(String arr[]){
        LinkedList l1 = new LinkedList();
        for (int i = 0; i < 9; i++){
            l1.append(i);
        }
        l1.delete(5);
        l1.print();
    }
}
