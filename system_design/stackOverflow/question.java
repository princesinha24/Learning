package system_design.stackOverflow;

import java.util.List;

abstract class statement {
    List<comment> comments;
    String body;
    int voteCount;
    userInterfcae author;

    public void upvote(){}

    public statement(String body, userInterfcae author) {
        this.body = body;
        this.comments = new java.util.ArrayList<>();
        this.author=author;
    }

    public void addComment(comment comm) {
        comments.add(comm);
    }


    public int getvoteCount() {
        return voteCount;
    }

    public String getBody() {
        return body;
    }

    public userInterfcae getAuthor(){
        return author;
    }

}

public class question extends statement {
    private List<answer> answers;
    private List<tag> tags;
    private String title;

    public question(String title, String body, userInterfcae author) {
        super(body, author);
        this.title = title;
        this.voteCount = 0;
        answers = new java.util.ArrayList<>();
        tags = new java.util.ArrayList<>();
    }

    public void addAnswer(answer ans) {
        answers.add(ans);
    }

    public void addTag(tag t) {
        tags.add(t);
        t.addQuestion(this);
    }

    @Override
    public void upvote() {
        voteCount++;
        author.updateScore(2);
    }

    public String getTitle() {
        return title;
    }

    public void printAnswer(){
        for(answer ans : answers){
            System.out.println(ans.getBody()+ "\t\t\t\t"+ ans.getAuthor().getName());
        }
    }
}
