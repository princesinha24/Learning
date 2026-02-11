package system_design.lift_design;

import java.util.*;

enum Direction{
    UP,
    DOWN,
    STILL
}

enum SourceType{
    INTERNAL,
    EXTERNAL
}
interface ElevatorInterface extends Runnable{
    void setState(elevatorState state);
    elevatorState getState();
    PriorityQueue<Integer> upRequest();
    PriorityQueue<Integer> downRequest();
    int currentFloor();
    void setCurrentFloor(int floor);
    void notify(String message);
    void addObserver(ObserverInterface observer);
    void start();
    void stop();
}

interface RequestInterface{
    int targetFloor();
    SourceType getSourceType();
    Direction getDirection();
}

interface ObserverInterface{
    void updateMessgae(String message);
}
interface elevatorState{
    void addRequest(ElevatorInterface lift, RequestInterface req);
    Direction getDirection();
    void move(ElevatorInterface lift);
}

class idealState implements elevatorState{
    @Override
    public Direction getDirection(){
        return Direction.STILL;
    }
    
    @Override
    public void move(ElevatorInterface lift){
        if(!lift.upRequest().isEmpty()){
            lift.setState(new upState());
        }
        else if(!lift.downRequest().isEmpty()){
            lift.setState(new downState());
        }
    }
    
    @Override
    public void addRequest(ElevatorInterface lift, RequestInterface req){
        if(lift.currentFloor()>req.targetFloor()){
            lift.downRequest().add(req.targetFloor());
        }
        else if(lift.currentFloor()<req.targetFloor()){
            lift.upRequest().add(req.targetFloor());
        }
    }
}

class upState implements elevatorState{
    @Override
    public Direction getDirection(){
        return Direction.UP;
    }
    
    @Override
    public void move(ElevatorInterface lift){
        if(lift.upRequest().isEmpty()){
            lift.setState(new idealState());
        }
        lift.setCurrentFloor(lift.currentFloor()+1);
        boolean flag=false;
        while(!lift.upRequest().isEmpty() && lift.upRequest().peek()<=lift.currentFloor()){
            lift.upRequest().poll();
            flag=true;
        }
        if (flag){
            lift.notify("Lift Opened at floor "+ lift.currentFloor());
        }
    }
    
    @Override
    public void addRequest(ElevatorInterface lift, RequestInterface req){
        if(req.getSourceType()==SourceType.INTERNAL){
            if(lift.currentFloor()>req.targetFloor()){
                lift.downRequest().add(req.targetFloor());
            }
            else if(lift.currentFloor()<req.targetFloor()){
                lift.upRequest().add(req.targetFloor());
            }
        }
        else{
            if(lift.currentFloor()<req.targetFloor() && req.getDirection()==Direction.UP){
                lift.upRequest().add(req.targetFloor());
            }
            else if(req.getDirection()==Direction.DOWN){
                lift.downRequest().add(req.targetFloor());
            }
        }
    } 
}


class downState implements elevatorState{
    @Override
    public Direction getDirection(){
        return Direction.UP;
    }
    
    @Override
    public void move(ElevatorInterface lift){
        if(lift.downRequest().isEmpty()){
            lift.setState(new idealState());
        }
        lift.setCurrentFloor(lift.currentFloor()-1);
        boolean flag=false;
        while(!lift.upRequest().isEmpty() && lift.upRequest().peek()>=lift.currentFloor()){
            lift.upRequest().poll();
            flag=true;
        }
        if (flag){
            lift.notify("Lift Opened at floor "+ lift.currentFloor());
        }
    }
    
    @Override
    public void addRequest(ElevatorInterface lift, RequestInterface req){
        if(req.getSourceType()==SourceType.INTERNAL){
            if(lift.currentFloor()>req.targetFloor()){
                lift.downRequest().add(req.targetFloor());
            }
            else if(lift.currentFloor()<req.targetFloor()){
                lift.upRequest().add(req.targetFloor());
            }
        }
        else{
            if(lift.currentFloor()>req.targetFloor() && req.getDirection()==Direction.DOWN){
                lift.downRequest().add(req.targetFloor());
            }
            else if(req.getDirection()==Direction.UP){
                lift.upRequest().add(req.targetFloor());
            }
        }
    } 
}

class request implements RequestInterface{
    private final int targetFloor;
    private final Direction dir;
    private final SourceType src;
    
    public request(int targetFloor, Direction dir){
        this.targetFloor=targetFloor;
        this.src=SourceType.EXTERNAL;
        this.dir=dir;
    }
    
    public request(int targetFloor, int sourceFloor){
        this.targetFloor=targetFloor;
        src=SourceType.INTERNAL;
        if(targetFloor>sourceFloor){
            dir=Direction.UP;
        }
        else if(targetFloor<sourceFloor){
            dir=Direction.DOWN;
        }
        else{
            dir=Direction.STILL;
        }
        
    }
    @Override
    public int targetFloor(){
        return targetFloor;
    }
    public SourceType getSourceType(){
        return src;
    }
    public Direction getDirection(){
        return dir;
    }
}

class Elevator implements ElevatorInterface{
    
    private elevatorState currState;
    private int currFloor;
    private PriorityQueue<Integer>up;
    private PriorityQueue<Integer>down;
    private List<ObserverInterface>observers;
    private boolean isRunning;
    public Elevator(int floor){
        currState=new idealState();
        currFloor=floor;
        up=new PriorityQueue<>();
        down=new PriorityQueue<>();
        observers=new ArrayList<>();
        isRunning=true;
    }
    
    @Override
    public void setState(elevatorState state){
        currState=state;
    }
    public elevatorState getState(){
        return currState;
    }
    public PriorityQueue<Integer> upRequest(){
        return up;
    }
    public PriorityQueue<Integer> downRequest(){
        return down;
    }
    public int currentFloor(){
        return currFloor;
    }
    public void setCurrentFloor(int floor){
        currFloor=floor;
    }
    public void notify(String message){
        for(ObserverInterface observer : observers){
            observer.updateMessgae(message);
        }
    }
    
    public void addObserver(ObserverInterface observer){
        observers.add(observer);
    }
    
    public void start(){
        isRunning=true;
    }
    
    public void stop(){
        isRunning=false;
    }
    
    public void run(){
        while(isRunning){
            currState.move(this);
            try{
                Thread.sleep(1000);
            }catch(InterruptedException e){
                Thread.currentThread().interrupt();
                stop();
            }
        }
    }
}

class display implements ObserverInterface{
    @Override
    public void updateMessgae(String Message){
        System.out.println(Message);
    }
}

class ElevatorSystem{
    private List<ElevatorInterface>elevators;
    private ElevatorSystem(int totalElevator){
        elevators=new ArrayList<>();
        while(totalElevator>0){
            elevators.add(new Elevator(0));
            elevators.get(elevators.size()-1).addObserver(new display());
            totalElevator--;
        }
    }
    private static ElevatorSystem obj=null;
    
    public static ElevatorSystem getInstanace(int totalElevator){
        if(obj==null){
            synchronized (ElevatorSystem.class){
                if(obj==null){
                    obj=new ElevatorSystem(totalElevator);
                }
            }
        }
        return obj;
    }

    public void start(){
        for(ElevatorInterface elv : elevators){
            new Thread(elv).start();
        }
    }

    public void sendRequest(RequestInterface req){
        
    }

}