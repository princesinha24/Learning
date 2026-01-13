package system_design.splitWise;

public class user{
    private final int id;
    private final String name;
    private balanceSheet balance;
    public user(int id, String name){
        this.id=id;
        this.name=name;
        balance=new balanceSheet(id);
    }
    public int getId(){
        return this.id;
    }
    public String getName(){
        return this.name;
    }

    public void updateBalance(user id, double amount){
        balance.update(id, amount);
    }

    public void printSheet(){
        System.out.println("Balance Sheet for User ID: "+name);
        balance.printSheet();
    }

    public balanceSheet getBalanceSheet(){
        return this.balance;
    }
}
