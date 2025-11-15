package system_design.stackOverflow;

import java.util.*;

public class stackFlowService {
    private List<userInterfcae> users;
    private List<tag> tags;
    private Map<tag,question> tagQuestionMap;
    public stackFlowService() {
        users = new java.util.ArrayList<>();
        tags = new java.util.ArrayList<>();
        tagQuestionMap = new java.util.HashMap<>();
    }
    public userInterfcae createUser(String name) {
        userInterfcae newUser = new user(name);
        users.add(newUser);
        return newUser;
    }

    public question postQuestion(String title, String body, userInterfcae author) {
        question newQuestion = new question(title, body, author);
        return newQuestion;
    }

    public answer postAnswer(String body, userInterfcae author, question q) {
        answer newAnswer = new answer(body, author);
        q.addAnswer(newAnswer);
        return newAnswer;
    }

    public void addComment(String content, userInterfcae author, statement stmt) {
        comment newComment = new comment(content, author);
        stmt.addComment(newComment);
    }

    public tag createTag(String name) {
        tag newTag = new tag(name);
        tags.add(newTag);
        return newTag;
    }

    public void tagQuestion(tag t, question q) {
        q.addTag(t);
        tagQuestionMap.put(t, q);
    }

    public List<question> getQuestionsByTag(tag t) {
        List<question> questions = new java.util.ArrayList<>();
        for (Map.Entry<tag, question> entry : tagQuestionMap.entrySet()) {
            if (entry.getKey().equals(t)) {
                questions.add(entry.getValue());
            }
        }
        return questions;
    }
}
