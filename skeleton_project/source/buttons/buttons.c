#include "../driver/elevio.h"
#include "../elevator/elevator.h"

void update_order_list(Elevator *elevator) {
    int stopState = elevio_stopButton();
    elevio_stopLamp(stopState);
    if (!stopState){
        for (int floor = 0; floor < N_FLOORS; floor++) {
            for (int button = 0; button < N_BUTTONS; button++) {
                if (!(floor == N_FLOORS - 1 && button == BUTTON_HALL_UP) && !(floor == 0 && button == BUTTON_HALL_DOWN)) {
                    // Makes sure not to turn off lights when button is released
                    if (elevio_callButton(floor, button) == 1) {
                        elevator->orderList[floor][button] = elevio_callButton(floor, button);
                    }
                }
            }
        }
    } else{
        elevator->state = stopped;
    }
    elevator->obstruction = elevio_obstruction();
}


