package system_design.vechileRental;

public class reservation {
    private vechile vec;
    private final customerInterface customer;
    private final int id;
    private int rentalPeriod; // in hours
    private int totalCost;
    private int percent; 

    public reservation(vechile vec, customerInterface customer, int rentalPeriod, int id) {
        this.vec = vec;
        this.customer = customer;
        this.rentalPeriod = rentalPeriod;
        this.id= id;
        percent = 10; // default 10% advance payment
        this.totalCost = vec.getPrice() * rentalPeriod;
    }

    void freeReservation(){
        vec.freeVechile();
    }
    int getTotalCost(){
        return totalCost;
    }

    vechile getVechile(){
        return vec;
    }

    int getRentalPeriod(){
        return rentalPeriod;
    }

    void setRentalPeriod(int rentalPeriod){
        this.rentalPeriod = rentalPeriod;
        this.totalCost = vec.getPrice() * rentalPeriod;
    }

    int getId(){
        return id;
    }

    void setAdvancePaymentPercentage(int percent){
        this.percent = percent;
    }
    int getAdvPayemnt(){
        return (totalCost*percent) / 10; // 10% advance payment
    }

    int getRemainingPayment(){
        return totalCost - getAdvPayemnt();
    }
}
