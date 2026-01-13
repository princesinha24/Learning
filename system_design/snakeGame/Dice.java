package system_design.snakeGame;

public class Dice {
    private final int totalDice;
    private final int face;
    public Dice(int n, int face){
        totalDice=n;
        this.face=face;
    }
    public int rollDice(){
        int total=(int)(Math.random()*totalDice*face+1)-(totalDice-1);
        return total;
    }
}
