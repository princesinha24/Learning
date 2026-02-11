package system_design.booking.entities;
import system_design.booking.enums.SeatType;
import system_design.booking.enums.SeatStatus;
public class Seat {
    private final SeatType type;
    private final int seatRow;
    private final int seatColumn;
    private SeatStatus status;
    public Seat(int row, int col, SeatType type){
        seatRow=row;
        seatColumn=col;
        this.type=type;
        status=SeatStatus.AVAILABLE;
    }

}
