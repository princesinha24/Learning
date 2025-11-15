package system_design.stackOverflow;

public class StackOverflow {
    public static void main(String[] args) {
        System.out.println("Welcome to StackOverflow System Design!");
        stackFlowService service = new stackFlowService();
        userInterfcae user1 = service.createUser("JohnDoe");
        userInterfcae user2 = service.createUser("JaneSmith");
        question q1 = service.postQuestion("What is Java?", "I want to know about Java programming language.", user1);
        service.postAnswer("Java is a coding language", user2, q1);
        service.postAnswer("Java is a compile time language", user2, q1);
        q1.printAnswer();
    }
}
