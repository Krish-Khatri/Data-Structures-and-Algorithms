public class Queue extends DoublyLinkedList{
    public boolean isEmpty(){
        return head == null;
    }

    public int peek(){
        return head.data;
    }

    public void push(int data){
        this.append(data);
    }

    public int pop(){
        int head_data = head.data;
        this.delete(head.data);
        return head_data;
    }

}
