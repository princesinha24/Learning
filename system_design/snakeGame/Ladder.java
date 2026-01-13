package system_design.snakeGame;

public class Ladder implements JumperInterface{
    private final int start;
    private final int end;
    
    private boolean validLadder(){
        if(start<end){
            return true;
        }
        return false;
    }

    public Ladder(int start, int end){
        this.start=start;
        this.end=end;
        if(!validLadder()){
            throw new IllegalArgumentException("Invalid Ladder");
        }
    }

    @Override
    public int getStart(){
        return this.start;
    }

    @Override
    public int jump(){
        return this.end;
    }
    
}
