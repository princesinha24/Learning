package system_design.atm_system;
import java.util.ArrayList;
import java.util.List;

interface noteDispatcher{
    public boolean withdraw(int amount, List<Integer> list);
    public void addQuantity(int quant);
}
class note implements noteDispatcher{
    private noteDispatcher next;
    int quantity;
    int val;
    private boolean decreaseQuantity(int quant){
        if(quantity<quant){
            return false;
        }
        quantity-=quant;
        return true;
    }
    public note(int val, noteDispatcher next){
        this.next=next;
        quantity=0;
        this.val=val;
    }
    @Override
    public void addQuantity(int quant){
        quantity+=quant;
    }
    @Override
    public boolean withdraw(int amount, List<Integer> list){
        int noOfNote=amount/val;
        if(noOfNote>quantity){
            noOfNote=quantity;
        }
        decreaseQuantity(noOfNote);
        amount-=(noOfNote*val);
        list.add(noOfNote);
        if(next!=null){
            boolean bool= next.withdraw(amount, list);
            if(!bool){
                addQuantity(noOfNote);
            }
            return bool;
        }
        else{
            if(amount!=0){
                addQuantity(noOfNote);
                return false;
            }
            else{
                return true;
            }
        }
    }
}

class cashDispatcher{
    private List<noteDispatcher> notes;
    public cashDispatcher() {
        notes = new ArrayList<>();
        notes.add(new note(20,null));
        notes.add(new note(50,notes.get(0)));
        notes.add(new note(100,notes.get(1)));
        notes.add(new note(200,notes.get(2)));
        notes.add(new note(500,notes.get(3)));
    }
    
    public void deposit(int[] banknotesCount) {
        for(int i=0;i<notes.size();i++){
            notes.get(i).addQuantity(banknotesCount[i]);
        }
    }
    
    public int[] withdraw(int amount) {
        List<Integer> ans=new ArrayList<>();
        if(notes.get(notes.size()-1).withdraw(amount, ans)){
           int[] arr = new int[5];
            for(int i=0;i<ans.size();i++){
                arr[ans.size()-1-i]=ans.get(i);
            }
            return arr;
        }
        return new int[]{-1};
    }
}
