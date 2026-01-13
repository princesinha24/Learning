package system_design.splitWise;

import java.util.ArrayList;
import java.util.List;

public class equalSplit implements interfaceSplit {
    public static equalSplit instance = null;
    public static equalSplit getInstance() {
        if(instance == null) {
            instance = new equalSplit();
        }
        return instance;
    }
    @Override
    public List<Double> split(List<user> users, List<Double> percent, double totalAmount){
        double splitAmount = totalAmount / users.size();
        List<Double>amount= new ArrayList<>();
        for(int i=0;i<users.size();i++){
            amount.add(splitAmount);
        }
        return amount;
    }
    
}
