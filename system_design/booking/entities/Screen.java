package system_design.booking.entities;
import java.util.ArrayList;
import java.util.List;
public class Screen {
    private List<Seat>seats;
    private final int id;
    public Screen(int id){
        seats=new ArrayList<>();
        this.id=id;
    }

    public void addSeat(Seat s){
        seats.add(s);
    }

    public List<Seat> getSeats(){
        return seats;
    }

    public int getId(){
        return id;
    }
}
