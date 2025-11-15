package system_design.stackOverflow;

public class answer extends statement{

    private boolean isAccepted;
    public answer(String content, userInterfcae author) {
        super(content, author);
        isAccepted = false;
    }

    @Override
    public void upvote() {
        voteCount++;
        author.updateScore(1);
    }

    public void acceptAnswer() {
        isAccepted = true;
    }

    public boolean isAccepted() {
        return isAccepted;
    }
    
}
