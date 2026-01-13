package system_design.foodDelivery;


import java.util.List;
interface menuInterface {
    void addItem(itemInterface item);
    void removeItem(String itemName);
    itemInterface getItem(String itemName);
    List<itemInterface> getAllItems();
    String getMenueName();
}


public class menu implements menuInterface {
    private final String menueName;
    private final List<itemInterface> items;

    public menu(String menueName, List<itemInterface> items) {
        this.menueName = menueName;
        this.items = items;
        items = new ArrayList<>();
    }

    @Override
    public void addItem(itemInterface item) {
        this.items.add(item);
    }

    @Override
    public void removeItem(String itemName) {
        this.items.removeIf(item -> item.getName().equals(itemName));
    }

    @Override
    public itemInterface getItem(String itemName) {
        for (itemInterface item : items) {
            if (item.getName().equals(itemName)) {
                return item;
            }
        }
        return null; // or throw an exception
    }

    @Override
    public List<itemInterface> getAllItems() {
        return this.items;
    }

    @Override
    public String getMenueName() {
        return this.menueName;
    }
    
}
