public class DoublyLinkedList {
    DoublyLinkedListNode head, tail;

    public void append(int data){
        if(head == null){
            head = new DoublyLinkedListNode(data);
            tail = head;
            return;
       }
        DoublyLinkedListNode temp = new DoublyLinkedListNode(data);
        temp.prev = tail;
        tail.next = temp;
        tail = temp;
    }

    public void delete(int data){
        if(head.data == data){
            head.next.prev = null;
            head = head.next;
        } else if(tail.data == data){
            tail.prev.next = null;
            tail = tail.prev;
        }
        else{
            DoublyLinkedListNode curr = head;
            while (curr != null){
                if(curr.data == data){
                    curr.prev.next = curr.next;
                    curr.next.prev = curr.prev;
                }
                curr = curr.next;
            }
        }
    }

    public void print(){
        DoublyLinkedListNode curr = head;
        while (curr != null){
            System.out.print(curr.data + "\n");
            curr = curr.next;
        }
    }
    public void reverse_print(){
        DoublyLinkedListNode curr = tail;
        while (curr != null){
            System.out.println(curr.data);
            curr = curr.prev;
        }
    }

    public static void main(String []arr){
        DoublyLinkedList d1 = new DoublyLinkedList();
        for(int i = 0; i < 9; i++){
            d1.append(i);
        }
        d1.print();
        d1.reverse_print();
        System.out.println("Delete Element with data = 5");
        d1. delete(5);
        System.out.println("Printing Linked List");
        d1.print();
        d1.reverse_print();
    }
}
