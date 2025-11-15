package system_design.stackOverflow;

interface userInterfcae{
    int getScore();
    String getName();
    void updateScore(int delta);
}

public class user implements userInterfcae {
    private String name;
    private int score;

    public user(String name) {
        this.name = name;
        score = 0;
    }

    @Override
    public int getScore() {
        return this.score;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public void updateScore(int delta) {
        this.score += delta;
    }
    
}
