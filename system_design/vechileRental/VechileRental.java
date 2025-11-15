package system_design.vechileRental;

import java.util.List;

public  class VechileRental {

    private static void printAvailableVechiles(List<vechile> vechiles){
        for(vechile v : vechiles){
            System.out.println("Vechile Number: " + v.getVechileNumber() + ", Type: " + v.getModel() + ", Price: " + v.getPrice());
        }
        // implement logic to print available vehicles
    }
    public static void main(String[] args) {
        bookingMgmt bookingManager= bookingMgmt.getInstnace();
        vechile vec1= bookingManager.addNewVechile(100, 1234, VechileType.CAR);
        int custId= bookingManager.addCustomer("John Doe", "DL123456");
        vechile vec2= bookingManager.addNewVechile(50, 5678, VechileType.BIKE);
        vechile vec3= bookingManager.addNewVechile(110, 9101, VechileType.CAR);
        printAvailableVechiles(bookingManager.getAvailableVechiles(VechileType.CAR));
        reservation res1= bookingManager.createBooking(custId, vec3, 5);
        printAvailableVechiles(bookingManager.getAvailableVechiles(VechileType.CAR));
    }
}
