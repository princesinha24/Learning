package system_design.splitWise;
import java.util.HashMap;
import java.util.Map;

public class balanceSheet {
    private final int owenerId;
    private Map<user, Double> amounts;
    public balanceSheet(int userId){
        owenerId=userId;
        amounts=new HashMap<>();
    }

    public void update(user id, double amount){
        if(!amounts.containsKey(id)){
            amounts.put(id, 0.0);
        }
        amounts.put(id, amounts.get(id)+amount);
        if(amounts.get(id)==0.0){
            amounts.remove(id);
        }
    }

    public void simplifyDebt(user id, double amount){
        if(!amounts.containsKey(id)){
            if(amount!=0.0){
                amounts.put(id, amount);  
            }
            return; 
        }
        if(amount==0.0){
            amounts.remove(id);
            return;
        }
        amounts.put(id, amount);
        return;
    }

    public double  cashOwed(){
        double total=0.0;
        for(Map.Entry<user, Double> entry:amounts.entrySet()){
            double amount = entry.getValue();
                total+=amount;
        }
        return total;
    }

    public void printSheet(){
        for(Map.Entry<user, Double> entry:amounts.entrySet()){
            user id = entry.getKey();
            double amount = entry.getValue();
            System.out.println("User "+id.getName()+" owes "+amount);
        }
    }
}
