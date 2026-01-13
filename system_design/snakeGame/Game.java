package system_design.snakeGame;

import java.util.ArrayList;
import java.util.List;

public class Game {
    public static void main(String[] args) {
        // System.out.println("Hello World");
        int boardSize = 100;
        
        List<Player> players = new ArrayList<>();
        Player p1 = new Player(1, "Alice");
        players.add(p1);
        Player p2 = new Player(2, "Singh");
        players.add(p2);
        Player p3 = new Player(3, "Aman");
        players.add(p3);

        List<JumperInterface> snakes = new ArrayList<>();
        JumperInterface snake1 = new Snake(14, 7);
        snakes.add(snake1);
        JumperInterface snake2 = new Snake(31, 26);
        snakes.add(snake2);
        JumperInterface snake3 = new Snake(38, 3);
        snakes.add(snake3);
        JumperInterface snake4 = new Snake(97, 32);
        snakes.add(snake4);
        JumperInterface snake5 = new Snake(95, 48);
        snakes.add(snake5);

        List<JumperInterface> ladders = new ArrayList<>();
        JumperInterface ladder1 = new Ladder(8, 15);
        ladders.add(ladder1);
        JumperInterface ladder2 = new Ladder(28, 84);
        ladders.add(ladder2);
        JumperInterface ladder3 = new Ladder(58, 77);
        ladders.add(ladder3);
        JumperInterface ladder4 = new Ladder(75, 86);
        ladders.add(ladder4);
        JumperInterface ladder5 = new Ladder(80, 97);
        ladders.add(ladder5);

        Dice dice = new Dice(1, 6);
        SnakeGame game = new SnakeGame(boardSize, snakes, ladders, players, dice);
        game.playGame();
    }
}
