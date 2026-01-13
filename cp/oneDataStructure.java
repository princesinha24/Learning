// package cp;
import java.util.*;
/*
    https://leetcode.com/problems/all-oone-data-structure/
*/
class Node{
    public Node next;
    public Node prev;
    private int count;
    private int freq;
    public Set<String> keys;
    public Node(int freq){
        next=null;
        prev=null;
        count=0;
        this.freq=freq;
        keys=new HashSet<>();
    }

    public void incCount(String key){
        count+=1;
        addString(key);
    }

    public void decCount(String key){
        count-=1;
        removeString(key);
    }

    public int getCount(){
        return count;
    }

    public int getFreq(){
        return freq;
    }

    private void addString(String st){
        keys.add(st);
    }

    private void removeString(String st){
        keys.remove(st);
    }
}


class AllOne {
    
    private Node head;
    private Node tail;
    private Map<String, Node>dict;

    private void deleteNode(Node curr){
        curr.prev.next=curr.next;
        curr.next.prev=curr.prev;
        curr.prev=null;
        curr.next=null;
    }

    private void insertNewNode(Node curr, int freq){
        Node newNode=new Node(freq);
        newNode.next=curr.next;
        newNode.prev=curr;
        curr.next.prev=newNode;
        curr.next=newNode;
    }

    private Node addNode(Node curr, String key){
        Node newNode;
        if(curr.next.getFreq()!=curr.getFreq()+1){
            insertNewNode(curr, curr.getFreq()+1);
            newNode=curr.next;
        }
        else{
            newNode=curr.next;
        }
        curr.decCount(key);
        newNode.incCount(key);

        if(curr.getCount()==0){
            deleteNode(curr);
        }
        return newNode;
    }

    public AllOne() {
        head=new Node(0);
        tail=new Node(0);
        head.next=tail;
        tail.prev=head;
        dict=new HashMap<>();
    }
    
    public void inc(String key) {
        if(dict.containsKey(key)){
            Node curr=addNode(dict.get(key),key);
            dict.put(key,curr);
        }
        else{
            if(head.next.getFreq()!=1){
                insertNewNode(head, 1);
            }
            head.next.incCount(key);
            dict.put(key,head.next);
        }
    }
    
    public void dec(String key) {
        Node curr=dict.get(key);
        if(curr.getFreq()==1){
            dict.remove(key);
        }
        else{
            if(curr.prev.getFreq()!=curr.getFreq()-1){
                insertNewNode(curr.prev, curr.getFreq()-1);
            }
            curr.prev.incCount(key);
            dict.put(key,curr.prev);
        }
        curr.decCount(key);
        if(curr.getCount()==0){
            deleteNode(curr);
        }
    }
    
    public String getMinKey() {
        if(head.next==tail){
            return "";
        }
        Iterator<String> iterator = head.next.keys.iterator();
        return iterator.next();
    }
    
    public String getMaxKey() {
        if(tail.prev==head){
            System.out.println("hello2");
            return "";
        }
        Iterator<String> iterator = tail.prev.keys.iterator();
        return iterator.next();
    }
}

public class oneDataStructure {
    public static void main(String[] args) {
        AllOne allOne = new AllOne();
        allOne.inc("hello");
        allOne.inc("hello");
        System.out.println(allOne.getMaxKey()); // return "hello"
        System.out.println(allOne.getMinKey()); // return "hello"
        allOne.inc("leet");
        System.out.println(allOne.getMaxKey()); // return "hello"
        System.out.println(allOne.getMinKey()); // return "leet"
    }
}
