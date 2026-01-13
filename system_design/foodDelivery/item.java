package system_design.foodDelivery;

interface itemInterface {
    void setQuantity(int quantity);
    int getQuantity();
    void setPrice(double price);
    double getPrice();
    String getName();
    String getDecrption();
}

class item implements itemInterface{
    private final String name;
    private final String decrption;
    private double price;
    private int quantity;

    public item(String name, String decrption, double price, int quantity) {
        this.name = name;
        this.decrption = decrption;
        this.price = price;
        this.quantity = quantity;
    }

    @Override
    public void setQuantity(int quantity) {
        this.quantity += quantity;
    }

    @Override
    public int getQuantity() {
        return this.quantity;
    }

    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public double getPrice() {
        return this.price;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public String getDecrption() {
        return this.decrption;
    }
} 

