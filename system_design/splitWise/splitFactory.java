package system_design.splitWise;

public class splitFactory{
    public static interfaceSplit getSplit(String splitType){
        if(splitType.equalsIgnoreCase("PERCENT")){
            return percentSplit.getInstance();
        }
        else if(splitType.equalsIgnoreCase("EQUAL")){
            return equalSplit.getInstance();
        }
        return null;
    }
}