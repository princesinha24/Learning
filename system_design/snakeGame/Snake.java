package system_design.snakeGame;
public class Snake implements JumperInterface{
    private final int start;
    private final int end;
    
    private boolean validSnake(){
        if(start>end){
            return true;
        }
        return false;
    }

    public Snake(int start, int end){
        this.start=start;
        this.end=end;
        if(!validSnake()){
            throw new IllegalArgumentException("Invalid Snake");
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
