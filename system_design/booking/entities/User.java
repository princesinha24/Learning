package system_design.booking.entities;

public class User {
    private final String name;
    private final String email;
    private final Address add;
    public User(String name, String email, Address add){
        this.name=name;
        this.email=email;
        this.add=add;
    }

    public String getName(){
        return name;
    }

    public String getEmail(){
        return email;
    }

    public Address getAddress(){
        return add;
    }
}
