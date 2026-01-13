package system_design.splitWise;

import java.util.List;

public class transection {
    private final user paidBy;
    private final double amount;

    private void updateBalanceSheet(List<user> involvedUsers, interfaceSplit splitType, List<Double> percent){
        List<Double>splits = splitType.split(involvedUsers, percent, this.amount);
        for(int i=0;i<involvedUsers.size();i++){
            user user = involvedUsers.get(i);
            if(user.getId()!=this.paidBy.getId()){
                user.updateBalance(this.paidBy, -1*splits.get(i));
                this.paidBy.updateBalance(user, splits.get(i));
            }
        }
    }
    
    public transection(user paidBy, double amount, List<user> involvedUsers, interfaceSplit splitType, List<Double> percent){
        this.paidBy=paidBy;
        this.amount=amount;
        updateBalanceSheet(involvedUsers,splitType, percent);
    }


}
