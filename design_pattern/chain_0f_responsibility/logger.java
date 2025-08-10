public enum LogLevel {
    INFO,
    DEBUG,
    WARN,
    ERROR
};

public interface Logger{
    void log(LogLevel level, String message);

}

public abstract class BaseLogger implements Logger{
    protected Logger nextLogger = null;
    public BaseLogger(Logger nextLogger) {
        this.nextLogger = nextLogger;
    }
}

public class ConsoleLogger extends BaseLogger {

    public ConsoleLogger(Logger nextLogger) {
        super(nextLogger);
    }

    @Override
    public void log(LogLevel level, String message) {
        if (level == LogLevel.INFO || level == LogLevel.DEBUG) {
            System.out.println("Console Logger: " + message);
        }
        if (nextLogger != null) {
            nextLogger.log(level, message);
        }
    }
}

public class WarnLogger extends BaseLogger {

    public FileLogger(Logger nextLogger) {
        super(nextLogger);
    }

    @Override
    public void log(LogLevel level, String message) {
        if (level == LogLevel.WARN) {
            System.out.println("File Logger: " + message);
        }
        if (nextLogger != null) {
            nextLogger.log(level, message);
        }
    }
}

public class ErrorLogger extends BaseLogger {

    public ErrorLogger(Logger nextLogger) {
        super(nextLogger);
    }

    @Override
    public void log(LogLevel level, String message) {
        if (level == LogLevel.ERROR) {
            System.out.println("Error Logger: " + message);
        }
        if (nextLogger != null) {
            nextLogger.log(level, message);
        }
    }
}

public class LoggerFactory {
    public static Logger createLogger() {
        Logger errorLogger = new ErrorLogger(null);
        Logger warnLogger = new WarnLogger(errorLogger);
        Logger consoleLogger = new ConsoleLogger(warnLogger);
        return consoleLogger;
    }
}

public class LoggerDemo {
    public static void main(String[] args) {
        Logger logger = LoggerFactory.createLogger();

        logger.log(LogLevel.INFO, "This is an info message.");
        logger.log(LogLevel.DEBUG, "This is a debug message.");
        logger.log(LogLevel.WARN, "This is a warning message.");
        logger.log(LogLevel.ERROR, "This is an error message.");
    }
}

