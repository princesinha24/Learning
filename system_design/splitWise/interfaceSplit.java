package system_design.splitWise;
import java.util.List;

interface interfaceSplit {
    List<Double> split(List<user> users, List<Double> percent, double totalAmount);
}
