package system_design.foodDelivery;

import java.util.List;
import java.util.Map;
interface  RestrauntInterface {
    // Define restaurant related methods here
    Location getLocation();
    String getName();
    List<menuInterface> getAllMenu();
    void addMenu(menuInterface menu);
}

public class restraunt implements RestrauntInterface {
    private final String name;
    private final Location location;
    private Map<String, menuInterface> menus;

    public RestrauntInterface(String name, Location location) {
        this.name = name;
        this.location = location;
        this.menus = new HashMap<>();
    }

    public void addMenu(menuInterface menu) {
        this.menus.put(menu.getMenueName(), menu);
    }

    public Location getLocation() {
        return this.location;
    }


}


