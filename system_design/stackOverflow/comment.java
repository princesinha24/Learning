package system_design.stackOverflow;



public class comment {
    private String content;
    private userInterfcae author;

    public comment(String content, userInterfcae author) {
        this.content = content;
        this.author = author;
    }

    public String getContent() {
        return content;
    }

    public String getAuthorName() {
        return author.getName();
    }

}
