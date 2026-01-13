package system_design.snakeGame;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

public class SnakeGame {
    private final List<JumperInterface> snakes;
    private final List<JumperInterface> ladders;
    private final Dice dice;
    private final int boardSize;
    private Map<Integer, Integer> playerPositions;
    private Queue<Player> turnQueue;
    public SnakeGame(int boardSize, List<JumperInterface> snakes, List<JumperInterface> ladders, List<Player> players, Dice dice){
        this.snakes=snakes;
        this.ladders=ladders;
        this.dice=dice;
        this.boardSize=boardSize;
        playerPositions=new HashMap<>();
        turnQueue=new LinkedList<>();
        // initialize player positions and turn queue
        for(Player p: players){
            playerPositions.put(p.getId(),0);
            turnQueue.add(p);
        }
    }

    public void playGame(){
        while(turnQueue.size()>1){
            Player currentPlayer=turnQueue.poll();
            int currentPosition=playerPositions.get(currentPlayer.getId());
            int diceRoll=dice.rollDice();
            int newPosition=currentPosition+diceRoll;
            if(newPosition>boardSize){
                turnQueue.add(currentPlayer);
                continue;
            }
            if(newPosition==boardSize){
                System.out.println(currentPlayer.getName()+" wins!");
                break;
            }
            for(JumperInterface snake:snakes){
                if(snake.getStart()==newPosition){
                    System.out.println(currentPlayer.getName()+" bitten by snake at "+newPosition);
                    newPosition=snake.jump();
                    break;
                }
            }

            for(JumperInterface ladder:ladders){
                if(ladder.getStart()==newPosition){
                    System.out.println(currentPlayer.getName()+" climbed ladder at "+newPosition);
                    newPosition=ladder.jump();
                    break;
                }
            }

            for(JumperInterface snake:snakes){
                if(snake.getStart()==newPosition){
                    System.out.println(currentPlayer.getName()+" bitten by snake at "+newPosition);
                    newPosition=snake.jump();
                    break;
                }
            }

            if(newPosition==boardSize){
                System.out.println(currentPlayer.getName()+" wins!");
                break;
            }
            playerPositions.put(currentPlayer.getId(),newPosition);
            System.out.println(currentPlayer.getName()+" moved to "+newPosition);
            turnQueue.add(currentPlayer);
        }
    }


}
