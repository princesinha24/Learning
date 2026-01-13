package system_design.splitWise;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

public class SplitWise {
    private static List<transection> transectionList;
    public static SplitWise instance = null;
    public static SplitWise getInstance() {
        if(instance == null) {
            instance = new SplitWise();
            transectionList = new ArrayList<>();
        }
        return instance;
    }

    public void createTransection(double amount, user paidBy, List<user> users, List<Double>percent ,String splitMethod) { 
        if(splitMethod.equals("EQUAL")) {
            interfaceSplit split = splitFactory.getSplit(splitMethod);
            transection t = new transection(paidBy, amount, users, split, null);
            transectionList.add(t);
        }
        else if(splitMethod.equals("PERCENT")) {
            interfaceSplit split = splitFactory.getSplit(splitMethod);
            transection t = new transection(paidBy, amount, users, split, percent);
            transectionList.add(t);
        }
        else{
            System.out.println("Invalid Split Method");
        }
    }

    public void simplifyDebt(List<user> users) {
        //To be implemented
        PriorityQueue<Double> creditors = new PriorityQueue<>();
        PriorityQueue<Double> debtors = new PriorityQueue<>();
        for(user u: users) {
            double balance = u.getBalanceSheet().cashOwed();
            if(balance > 0) {
                creditors.add(balance);
            } else if(balance < 0) {
                debtors.add(-1 * balance);
            }
        }
        
    }
}
