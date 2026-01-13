package system_design.foodDelivery;

public class Location {
    private final double latitude;
    private final double longitude;
    private final int locationId;

    public Location(double latitude, double longitude,int id) {
        this.latitude = latitude;
        this.longitude = longitude;
        this.locationId = id;
    }

    public int getId(){
        return this.locationId;
    }
}
