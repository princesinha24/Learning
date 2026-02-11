import java.util.ArrayDeque;
import java.util.Deque;

// 1) Command interface
interface Command {
    void execute();
    void undo();
}

// 2) Receivers: the actual business objects
class Light {
    private boolean on = false;

    public void on() {
        on = true;
        System.out.println("Light is ON");
    }

    public void off() {
        on = false;
        System.out.println("Light is OFF");
    }

    public boolean isOn() {
        return on;
    }
}

class Fan {
    enum Speed { OFF, LOW, MEDIUM, HIGH }
    private Speed speed = Speed.OFF;

    public void setSpeed(Speed s) {
        speed = s;
        System.out.println("Fan speed: " + speed);
    }

    public Speed getSpeed() {
        return speed;
    }
}

// 3) Concrete Commands
class LightOnCommand implements Command {
    private final Light light;

    public LightOnCommand(Light light) {
        this.light = light;
    }

    public void execute() {
        light.on();
    }

    public void undo() {
        light.off();
    }
}

class LightOffCommand implements Command {
    private final Light light;

    public LightOffCommand(Light light) {
        this.light = light;
    }

    public void execute() {
        light.off();
    }

    public void undo() {
        light.on();
    }
}

class FanSetSpeedCommand implements Command {
    private final Fan fan;
    private final Fan.Speed newSpeed;
    private Fan.Speed prevSpeed;

    public FanSetSpeedCommand(Fan fan, Fan.Speed newSpeed) {
        this.fan = fan;
        this.newSpeed = newSpeed;
    }

    public void execute() {
        prevSpeed = fan.getSpeed();
        fan.setSpeed(newSpeed);
    }

    public void undo() {
        fan.setSpeed(prevSpeed);
    }
}

// 4) Invoker: triggers commands (doesn't know how they work)
class RemoteControl {
    private final Deque<Command> history = new ArrayDeque<>();

    public void press(Command command) {
        command.execute();
        history.push(command);
    }

    public void pressUndo() {
        if (history.isEmpty()) {
            System.out.println("Nothing to undo");
            return;
        }
        history.pop().undo();
    }
}

// 5) Client: wires everything together

public class remote {
    public static void main(String[] args) {
        Light light = new Light();
        Fan fan = new Fan();

        Command lightOn = new LightOnCommand(light);
        Command lightOff = new LightOffCommand(light);
        Command fanHigh = new FanSetSpeedCommand(fan, Fan.Speed.HIGH);
        Command fanLow = new FanSetSpeedCommand(fan, Fan.Speed.LOW);

        RemoteControl remote = new RemoteControl();

        remote.press(lightOn);
        remote.press(fanHigh);
        remote.press(fanLow);
        remote.press(lightOff);

        remote.pressUndo(); // undo lightOff -> lightOn
        remote.pressUndo(); // undo fanLow -> fanHigh
        remote.pressUndo(); // undo fanHigh -> previous speed
    }
    
}
