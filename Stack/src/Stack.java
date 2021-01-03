public class Stack {
    Node top;

    public void push(int data){
        if(top == null){
            top = new Node(data);
            return;
        }

        Node temp = new Node(data);
        temp.next = top;
        top = temp;
    }

    public int pop(int data){
        int top_data = top.data;
        top = top.next;
        return top_data;
    }

    public boolean is_empty(){
        return top == null;
    }

    public int peek(){
        return top.data;
    }
}
