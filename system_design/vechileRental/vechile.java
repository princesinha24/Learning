package system_design.vechileRental;

enum VechileType {
    CAR,
    BIKE,
    TRUCK
}

enum VechileStatus {
    AVAILABLE,
    RENTED,
    RENTALINPROGRESS,
    MAINTENANCE
}



public interface  vechile {
    VechileType getModel();
    int getVechileNumber();
    int getPrice();
    VechileStatus isAvailable();
    void bookVechile();
    void freeVechile();
    void setPrice(int price);
    void setStatus(VechileStatus status);
}

abstract class vechileClass implements vechile {
    private VechileStatus status;
    private final int vechileNumber;
    private int price;

    public vechileClass(int price, int vechileNumber) {
        this.price=price;
        this.vechileNumber=vechileNumber;
        status=VechileStatus.AVAILABLE;
    }


    @Override
    public int getVechileNumber() {
        return vechileNumber;
    }

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public VechileStatus isAvailable() {
        return status;
    }

    @Override
    public void bookVechile() {
        status=VechileStatus.RENTED;
    }

    @Override
    public void freeVechile() {
        status=VechileStatus.AVAILABLE;
    }

    @Override
    public void setPrice(int price) {
        this.price=price;
    }

    @Override
    public void setStatus(VechileStatus status) {
        this.status = status;
    }

}

class Car extends vechileClass {
    public Car(int price, int vechileNumber) {
        super(price, vechileNumber);
    }

    @Override
    public VechileType getModel() {
        return VechileType.CAR;
    }
}

class Bike extends vechileClass {
    public Bike(int price, int vechileNumber) {
        super(price, vechileNumber);
    }

    @Override
    public VechileType getModel() {
        return VechileType.BIKE;
    }
}

class Truck extends vechileClass {
    public Truck(int price, int vechileNumber) {
        super(price, vechileNumber);
    }

    @Override
    public VechileType getModel() {
        return VechileType.TRUCK;
    }
}

