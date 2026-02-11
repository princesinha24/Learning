package system_design.booking.entities;

public class Address {
    private final String City;
    private final String pincode;
    private final String firstLine;

    public Address(String city, String pincode, String location) {
        this.City = city;
        this.pincode = pincode;
        this.firstLine = location;
    }

}
