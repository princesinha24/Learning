package system_design.splitWise;
import java.util.List;
public class splitWiseMain {
    public static void main(String[] args) {
        List<user> userList = new java.util.ArrayList<>();
        SplitWise splitWise = SplitWise.getInstance();
        user u1 = new user(1, "Alice");
        userList.add(u1);
        user u2 = new user(2, "Bob");
        userList.add(u2);
        user u3 = new user(3, "Charlie");
        userList.add(u3);
        user u4 = new user(4, "David");
        userList.add(u4);
        user u5 = new user(5, "Eve");
        userList.add(u5);
        user u6 = new user(6, "Frank");
        userList.add(u6);

        splitWise.createTransection(1200, u1, java.util.Arrays.asList(u1, u2, u3, u4), null, "EQUAL");
        splitWise.createTransection(1500, u2, java.util.Arrays.asList(u1, u2, u3, u4), java.util.Arrays.asList(25.0, 25.0, 30.0, 20.0), "PERCENT");
        
        System.out.println("Balance Sheets after first two transactions:");
        for(user u : userList) {
            u.printSheet();
        }

        user u7 = new user(7, "Grace");
        userList.add(u7);
        splitWise.createTransection(2000, u7, java.util.Arrays.asList(u1, u2, u4, u5, u6, u7), null, "EQUAL");
        System.out.println("/n/n Balance Sheets after first next transectio:");
        for(user u : userList) {
            u.printSheet();
        }
    }
}
