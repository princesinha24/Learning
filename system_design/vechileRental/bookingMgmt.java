package system_design.vechileRental;
import java.util.*;

public class bookingMgmt {
    private Map<VechileType, List<vechile>>availableVichile = new HashMap<>();
    private List<reservation> reservations = new ArrayList<>();
    private List<customerInterface> customers = new ArrayList<>();
    private static bookingMgmt instance = null;
    
    public static bookingMgmt getInstnace(){
        if(instance == null){
            instance = new bookingMgmt();
        }
        return instance;
    }

    private void addVechile(vechile vec){
        if(!availableVichile.containsKey(vec.getModel())){
            availableVichile.put(vec.getModel(), new ArrayList<>());
        }
        availableVichile.get(vec.getModel()).add(vec);
    }

    private boolean makeAdvancePayemnt(int amount){
        // dummy implementation of payment gateway
        return true;
    }

    vechile addNewVechile(int price, int vechileNumber, VechileType type){
        vechile vec = null;
        switch(type){
            case CAR:
                vec = new Car(price, vechileNumber);
                break;
            case BIKE:
                vec = new Bike(price, vechileNumber);
                break;
            case TRUCK:
                vec = new Truck(price, vechileNumber);
                break;
        }
        if(vec != null){
            addVechile(vec);
            return vec;
        }
        return null;

    }

    int addCustomer(String name, String drivingLicenseNumber){
        int customerId = customers.size() + 1;
        customers.add(new customer(customerId, name, drivingLicenseNumber));
        return customerId;
    }

    reservation createBooking(int customerId, vechile vec, int rentalPeriod){
        // System.out.println("customerId: " + customerId);
        if(customerId <= 0 || customerId > customers.size() || vec.isAvailable() != VechileStatus.AVAILABLE){
            return null;
        }
        customerInterface cus=customers.get(customerId-1);
        if(cus==null){
            return null;
        }
        vec.setStatus(VechileStatus.RENTALINPROGRESS);
        reservation newRes = new reservation(vec, cus, rentalPeriod, reservations.size() + 1);
        reservations.add(newRes);
        
        if(makeAdvancePayemnt(newRes.getAdvPayemnt())){
            vec.bookVechile();
            availableVichile.get(vec.getModel()).remove(vec);
            System.out.println("Booking successful. Reservation ID: " + newRes.getId());
            return newRes;
        } else {
            newRes.freeReservation();
            reservations.remove(newRes);
            return null;
        }
    }

    Boolean cancelBooking(reservation res){
        if(res == null || !reservations.contains(res)){
            return false;
        }
        res.freeReservation();
        reservations.remove(res);
        availableVichile.get(res.getVechile().getModel()).add(res.getVechile());
        return true;
    }

    List<vechile> getAvailableVechiles(VechileType type){
        if(!availableVichile.containsKey(type)){
            return new ArrayList<>();
        }
        return availableVichile.get(type);
    }

}
