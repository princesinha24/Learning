import java.util.*;


interface BankingSystem{
    boolean CreateAccount(int time, String name);
    int deposite(int time, String name, int amount);
    int transfer(int time, String src, String dst, int amount);
    int withdraw(int time, String name, int amount);
    List<String>maxWithdrawList(int time);
    int scheduletransection(int time, int id, int delay, Object... args);
    boolean deleteTransection(int time, int id, String src);
}

interface AccountInterface extends Comparable<AccountInterface>{
    int depositeAmount(int amount);
    int getAmount();
    int getWithdraw();
    int withdraw(int amount);
    String getName();
}



class Transection implements Comparable<Transection>{
    int id, type, timetoExecute, amount;
    String srcname;
    String dstname;
    Transection(int id, int type, int time, int amount, List<String> src){
        this.id=id;
        this.type=type;
        this.timetoExecute=time;
        this.srcname = src.get(0);
        this.amount=amount;
        if(src.size()==2){
            this.dstname = src.get(1);
        }
        else{
            this.dstname="";
        }
    }
    
    public int getId(){
        return id;
    }
    
    public int getTime(){
        return timetoExecute;
    }
    
    public String getName(){
        return srcname;
    }
    
    @Override
    public int compareTo(Transection trans){
        if(trans.getTime()!=this.getTime()){
            return this.getTime()-trans.getTime();
        }
        return this.getId() - trans.getId();
    }
    
}

class Account implements AccountInterface{
    private String name;
    private int credit;
    private int withdraw;
    Account(String name){
        this.name=name;
        credit=0;
        withdraw=0;
    }
    
    @Override
    public int getAmount(){
        return credit;
    }
    
    @Override
    public int depositeAmount(int amount){
        credit+=amount;
        return getAmount();
    }
    
    @Override 
    public int getWithdraw(){
        return withdraw;
    }
    
    @Override 
    public int withdraw(int amount){
        credit-=amount;
        withdraw+=amount;
        return getWithdraw();
    }
    
    @Override
    public String getName(){
        return name;
    }
    
    @Override
    public int compareTo(AccountInterface acc){
        if(acc.getWithdraw()!= this.getWithdraw()){
            return acc.getWithdraw() - this.getWithdraw();
        }
        return this.getName().compareTo(acc.getName());
    }
}

class BankingSystemManagemet implements BankingSystem{
    private HashMap<String, AccountInterface> mp = new HashMap<>(); 
    private int transectionId=0;
    private HashMap<Integer, Transection>trans = new HashMap<>();
    private PriorityQueue<Transection>pqT= new PriorityQueue<>();
    private boolean validateTransection(Transection tq, String name){
        if(tq.getName().compareTo(name)!=0){
            return false;
        }
        return true;
    }
    private AccountInterface getAccount(String name){
        if(mp.containsKey(name)){
            return mp.get(name);
        }
        return null;
    }
    
    private void executeTransection(int time){
        while(!pqT.isEmpty()){
            if(pqT.peek().getTime()>time){
                return;
            }
            Transection tempTrans = pqT.poll();
            if(trans.containsKey(tempTrans.getId())){
                switch (tempTrans.getId()){
                    case 1:
                        accountCreation(tempTrans.getName());
                        break;
                    case 2:
                        depositeLocal(tempTrans.getName(), tempTrans.amount);
                        break;
                    case 3:
                        transferLocal(tempTrans.getName(), tempTrans.dstname, tempTrans.amount);
                        break;
                    default :
                        withdrawLocal(tempTrans.getName(), tempTrans.amount);
                        break;                
                }
            }
            trans.remove(tempTrans.getId());
        }
        return;
    }
    
    
    private boolean accountCreation(String name){
        if(getAccount(name)!=null){
            System.out.println("Account already exist for " + name);
            return false;
        }
        mp.put(name, new Account(name));
        return true;
    }
    
    private int depositeLocal(String name, int amount){
        AccountInterface acc=getAccount(name);
        if(acc==null){
            return -1;
        }
        return acc.depositeAmount(amount);
    }
    
    private int transferLocal(String src, String dst, int amount){
        AccountInterface srcAcc=getAccount(src);
        AccountInterface dstAcc=getAccount(dst);
        if(srcAcc==null || dstAcc == null || srcAcc == dstAcc || srcAcc.getAmount()<amount){
            return -1;
        }
        int val=srcAcc.withdraw(amount);
        dstAcc.depositeAmount(amount);
        return val;
    }
    
    private int withdrawLocal(String name, int amount){
        AccountInterface acc=getAccount(name);
        if(acc==null){
            return -1;
        }
        return acc.withdraw(amount);
    }
    @Override
    public boolean CreateAccount(int time, String name){
        executeTransection(time);
        return accountCreation(name);
    }
    
    @Override
    public int deposite(int time, String name, int amount){
        executeTransection(time);
        return depositeLocal(name, amount);
    }
    
    @Override
    public int transfer(int time, String src, String dst, int amount){
        executeTransection(time);
        return transferLocal(src, dst, amount);
    }
    
    @Override
    public int withdraw(int time, String name, int amount){
        executeTransection(time);
        return withdrawLocal(name, amount);   
    }
    
    @Override
    public List<String>maxWithdrawList(int time){
        executeTransection(time);
        PriorityQueue<AccountInterface> pq= new PriorityQueue<>();
        for (Map.Entry<String, AccountInterface> entry : mp.entrySet()) {
            pq.add(entry.getValue());
        }
        List<String> ans= new ArrayList<>();
        while(!pq.isEmpty()){
            AccountInterface acc=pq.poll();
            ans.add("{" +acc.getName() + " "+acc.getWithdraw() + "}");
        }
        return ans;
    }
    
    @Override
    public int scheduletransection(int time, int id, int delay, Object... args){
        executeTransection(time);
        transectionId++;
        List<String> st= new ArrayList<>();
        int amount=0;
        for(Object arg :args){
            if(arg instanceof String){
                st.add(arg.toString());
            }
            if(arg instanceof Integer){
                amount=(Integer)arg;
            }
        }
        Transection newTran = new Transection(transectionId, id, time+delay,amount, st);
        trans.put(transectionId, newTran);
        pqT.add(newTran);
        return transectionId;
    }
    
    @Override
    public boolean deleteTransection(int time, int id, String src){
        executeTransection(time);
        if(!trans.containsKey(id) || !validateTransection(trans.get(id), src)){
            return false;
        }
        trans.remove(id);
        return true;
    }
}

public class basicBanking {
    private static void printList(List<String> s){
        for(int i=0;i<s.size();i++){
            System.out.print(s.get(i) + " ");
        }
        System.out.println();
    }
    public static void main(String []args){
        int i=0;
        BankingSystem bak = new BankingSystemManagemet();
        bak.CreateAccount(++i,"Prince");
        bak.CreateAccount(++i,"Roshan");
        bak.CreateAccount(++i,"Xyz");
        bak.CreateAccount(++i,"Name");
        bak.deposite(++i,"Prince", 1000);
        bak.deposite(++i,"Xyz", 2000);
        bak.deposite(++i,"Name", 100);
        bak.deposite(++i,"Roshan", 3500);
        bak.transfer(++i,"Roshan", "Xyz", 1000);
        bak.transfer(++i,"Xyz", "Name", 300);
        bak.withdraw(++i,"Prince", 200);
        printList(bak.maxWithdrawList(++i));
        bak.scheduletransection(++i, 1, 5, "Crazy");
        bak.scheduletransection(++i, 2, 4, "Crazy", 10000);
        bak.deposite(++i, "Prince", 3000);
        bak.scheduletransection(++i, 3, 3, "Prince", "Roshan", 2000);
        bak.withdraw(++i, "Roshan", 1500);
        printList(bak.maxWithdrawList(++i));
        printList(bak.maxWithdrawList(++i));
    }
}