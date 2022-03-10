#include "stdio.h"
#include "../driver/elevio.h"
#include "elevator.h"
#include "../door/door.h"
#include "time.h"
#include "string.h"


Elevator initialize() {
    door_close();
    int floor = elevio_floorSensor();
    if (floor < 0) {
        elevio_motorDirection(1);
        while (floor < 0) {
            floor = elevio_floorSensor();

        }

        elevio_motorDirection(0);
    }
    Elevator elevator;
    elevator.state = idle;
    elevator.lastFloor = floor;
    elevator.obstruction = 0;
    elevator.lastDirection = up;
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button < N_BUTTONS; button++) {
            if (!(floor == N_FLOORS - 1 && button == BUTTON_HALL_UP) && !(floor == 0 && button == BUTTON_HALL_DOWN)) {
                elevator.orderList[floor][button] = 0;
            }
        }
    }
    elevator.door = closed;
    return elevator;
}

int check_orders_over(int currentFloor, Elevator *elevator) {
    int orderOverCurrentFloor = 0;
    for (int i = currentFloor; i < N_FLOORS; ++i) {
        if (currentFloor != i) {
            if (elevator->orderList[i][0] == 1) {
                orderOverCurrentFloor = 1;
            } else if (elevator->orderList[i][1] == 1) {
                orderOverCurrentFloor = 1;
            } else if (elevator->orderList[i][2] == 1) {
                orderOverCurrentFloor = 1;
            }
        }
    }
    return orderOverCurrentFloor;
}

int check_orders_under(int currentFloor, Elevator *elevator) {
    int orderUnderCurrentFloor = 0;
    for (int i = currentFloor; i >= 0; --i) {
        if (currentFloor != i) {
            if (elevator->orderList[i][0] == 1) {
                orderUnderCurrentFloor = 1;
            } else if (elevator->orderList[i][1] == 1) {
                orderUnderCurrentFloor = 1;
            } else if (elevator->orderList[i][2] == 1) {
                orderUnderCurrentFloor = 1;
            }
        }
    }
    return orderUnderCurrentFloor;
}

void check_if_stop_at_floor_up(Elevator *elevator) {
    int currentFloor = elevio_floorSensor();
    if (currentFloor >= 0) {
        elevator->lastFloor = currentFloor;
        if (elevator->orderList[currentFloor][0] == 1 || elevator->orderList[currentFloor][2] == 1) {
            elevator->state = loading;
        } else {
            int orderOver = check_orders_over(currentFloor, elevator);
            if (orderOver == 0) {
                elevator->lastDirection = down;
                elevator->state = idle;

            } else if (orderOver == 1) {
                elevator->state = movingUp;
            }

        }
    }
}

void check_if_stop_at_floor_down(Elevator *elevator) {
    int currentFloor = elevio_floorSensor();

    if (currentFloor >= 0) {
        elevator->lastFloor = currentFloor;
        if (elevator->orderList[currentFloor][1] == 1 || elevator->orderList[currentFloor][2] == 1) {

            elevator->state = loading;
        } else {
            int orderUnder = check_orders_under(currentFloor, elevator);
            if (orderUnder == 0) {
                elevator->lastDirection = up;
                elevator->state = idle;

            } else if (orderUnder == 1) {
                elevator->state = movingDown;
            }

        }
    }
}

void clear_order(Elevator *elevator) {
    int currentfloor = elevio_floorSensor();
    if (elevator->lastDirection == up) {
        elevator->orderList[currentfloor][0] = 0;
        elevator->orderList[currentfloor][2] = 0;
        if (currentfloor == N_FLOORS - 1) {
            elevator->orderList[currentfloor][1] = 0;
            elevator->orderList[currentfloor][2] = 0;
        }
    } else if (elevator->lastDirection == down) {
        elevator->orderList[currentfloor][1] = 0;
        elevator->orderList[currentfloor][2] = 0;
        if (currentfloor == 0) {
            elevator->orderList[currentfloor][0] = 0;
            elevator->orderList[currentfloor][2] = 0;
        }
    }
}

void clear_all_orders(Elevator *elevator) {
    memset(elevator->orderList, 0, sizeof(elevator->orderList[0][0]) * N_FLOORS * N_BUTTONS);
}

void check_state(Elevator *elevator) {
    switch (elevator->state) {
        case movingUp:
            moving_up_case(elevator);
            break;
        case movingDown:
            moving_down_case(elevator);
            break;
        case stopped:
            stopped_case(elevator);
            break;
        case loading:
            loading_case(elevator);
            break;
        case idle:
            idle_case(elevator);
            break;
    }
}

void moving_up_case(Elevator *elevator) {
    elevio_motorDirection(1);
    elevator->lastDirection = up;
    check_if_stop_at_floor_up(elevator);
}

void moving_down_case(Elevator *elevator) {
    elevio_motorDirection(-1);
    check_if_stop_at_floor_down(elevator);
    elevator->lastDirection = down;
}

void loading_case(Elevator *elevator) {
    elevio_motorDirection(0);
    time_t currentTime = time(NULL);
    if (elevator->door == closed) {
        door_open();
        elevator->door = open;
        timeDoorOpened = time(NULL);

    } else if (currentTime - timeDoorOpened >= 3) {
        if (elevator->obstruction == 1) {
            timeDoorOpened = time(NULL);
        } else {
            door_close();
            elevator->door = closed;
            clear_order(elevator);
            elevator->state = idle;
        }
    }
}

void idle_case(Elevator *elevator) {
    elevio_motorDirection(0);
    if (elevator->lastDirection == up) {
        check_if_stop_at_floor_up(elevator);
        if (elevator->state == idle) {
            check_if_stop_at_floor_down(elevator);
        }
    } else if (elevator->lastDirection == down) {
        check_if_stop_at_floor_down(elevator);
        if (elevator->state == idle) {
            check_if_stop_at_floor_up(elevator);
        }

    }
}

void stopped_case(Elevator *elevator) {
    elevio_motorDirection(0);
    clear_all_orders(elevator);
    elevator->state = idle;
}