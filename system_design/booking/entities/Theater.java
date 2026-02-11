package system_design.booking.entities;
import java.util.ArrayList;
import java.util.List;
public class Theater {
    private final Address address;
    private List<Screen>screens;
    private final int id;
    public Theater(Address address, int id){
        screens=new ArrayList<>();
        this.address=address;
        this.id=id;
    }

    public addScreen(Screen s){
        screens.add(s);
    }
}
