package system_design.splitWise;
import java.util.List;
public class percentSplit implements interfaceSplit {
    public static percentSplit instance = null;
    public static percentSplit getInstance() {
        if(instance == null) {
            instance = new percentSplit();
        }
        return instance;
    }
    
    @Override
    public List<Double> split(List<user> users, List<Double> percent, double totalAmount) {
        List<Double> splits = new java.util.ArrayList<>();
        for(int i=0;i<users.size();i++){
            splits.add((percent.get(i)/100)*totalAmount);
        }
        return splits;
    }
    
}
