import java.util.*;

// 1. Dice Interface (Dependency Inversion)
interface Dice {
    int roll();
}

// Concrete Dice
class NormalDice implements Dice {
    private final Random random = new Random();
    public int roll() {
        return random.nextInt(6) + 1;
    }
}

// 2. Player Class (Single Responsibility)
class Player {
    private String name;
    private int position = 0;

    public Player(String name) {
        this.name = name;
    }

    public String getName() { return name; }
    public int getPosition() { return position; }
    public void setPosition(int pos) { this.position = pos; }
}

// 3. Abstract Jump (Liskov + Open/Closed)
abstract class Jump {
    protected int start;
    protected int end;

    public Jump(int start, int end) {
        this.start = start;
        this.end = end;
    }

    public boolean isOnStart(int position) {
        return this.start == position;
    }

    public int getEnd() {
        return this.end;
    }
}

// Snake inherits Jump
class Snake extends Jump {
    public Snake(int start, int end) {
        super(start, end);
    }
}

// Ladder inherits Jump
class Ladder extends Jump {
    public Ladder(int start, int end) {
        super(start, end);
    }
}

// 4. Board Class (Single Responsibility)
class Board {
    private List<Jump> jumps = new ArrayList<>();

    public void addJump(Jump jump) {
        jumps.add(jump);
    }

    public int getNewPosition(int position) {
        for (Jump j : jumps) {
            if (j.isOnStart(position)) {
                return j.getEnd();
            }
        }
        return position;
    }
}

// 5. Game Class (Uses Dependency Injection & Open/Closed)
class Game {
    private final int WIN = 100;
    private Dice dice;
    private Board board;
    private Queue<Player> players;

    // Inject dependencies via constructor
    public Game(Dice dice, Board board, List<Player> playerList) {
        this.dice = dice;
        this.board = board;
        this.players = new LinkedList<>(playerList);
    }

    public void start() {
        System.out.println("🎮 Game Started!");

        while (true) {
            Player current = players.poll(); // Player's turn
            int roll = dice.roll();
            System.out.println(current.getName() + " rolled: " + roll);

            int newPos = current.getPosition() + roll;
            if (newPos > WIN) {
                players.offer(current);
                continue;
            }

            newPos = board.getNewPosition(newPos);
            current.setPosition(newPos);
            System.out.println(current.getName() + " moved to position: " + newPos);

            if (newPos == WIN) {
                System.out.println("🏆 " + current.getName() + " wins!");
                break;
            }
            players.offer(current);
        }
    }
}

// Main Class
public class snake_ladder {
    public static void main(String[] args) {
        // Creating Board
        Board board = new Board();
        board.addJump(new Snake(99, 10));
        board.addJump(new Snake(92, 35));
        board.addJump(new Ladder(5, 25));
        board.addJump(new Ladder(20, 60));

        // Players
        List<Player> playerList = Arrays.asList(
            new Player("Player 1"),
            new Player("Player 2")
        );

        // Use Dice interface for loose coupling
        Game game = new Game(new NormalDice(), board, playerList);
        game.start();
    }
}
