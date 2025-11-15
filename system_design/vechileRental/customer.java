package system_design.vechileRental;

interface customerInterface {
    int getCustomerId();
    String getCustomerName();
    String getDrivingLicenseNumber();
}

class customer implements customerInterface{
    private final int customerId;
    private final String customerName;
    private final String drivingLicenseNumber;

    public customer(int customerId, String customerName, String drivingLicenseNumber) {
        this.customerId = customerId;
        this.customerName = customerName;
        this.drivingLicenseNumber = drivingLicenseNumber;
    }

    @Override
    public int getCustomerId() {
        return customerId;
    }

    @Override
    public String getCustomerName() {
        return customerName;
    }

    @Override
    public String getDrivingLicenseNumber() {
        return drivingLicenseNumber;
    }
    
}
