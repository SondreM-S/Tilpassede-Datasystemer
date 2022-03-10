//#include "../dependency.h"
#include "../driver/elevio.h"
#include "../elevator/elevator.h"

void lights_update_from_orderlist(Elevator *elevator) {
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button < N_BUTTONS; button++) {
            if (elevator->orderList[floor][button] == 1) {
                elevio_buttonLamp(floor, button, 1);
            } else {
                elevio_buttonLamp(floor, button, 0);
            }
        }
    }
}

void set_light_valid_floor_level (Elevator *elevator) {
    elevio_floorIndicator(elevator->lastFloor);
}