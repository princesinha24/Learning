package system_design.stackOverflow;

import java.util.Set;


public class tag{
    private Set<question> questions;
    private final String name;
    public tag(String name) {
        this.name = name;
        this.questions = new java.util.HashSet<>();
    }

    public String getName() {
        return name;
    }

    public void addQuestion(question q) {
        questions.add(q);
    }
    
    public void removeQuestion(question q) {
        questions.remove(q);
    }

    public Set<question> getQuestions() {
        return questions;
    }

    public boolean questionExists(question q) {
        return questions.contains(q);
    }
}
