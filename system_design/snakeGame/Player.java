package system_design.snakeGame;

public class Player {
    private final int id;
    private final String name;
    public Player(int id, String name){
        this.id=id;
        this.name=name;
    }

    public int getId(){
        return this.id;
    }

    public String getName(){
        return this.name;
    }
}
