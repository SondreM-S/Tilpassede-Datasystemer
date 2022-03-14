#include <stdio.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator/elevator.h"
#include "buttons/buttons.h"
#include "lights/lights.h"


/**
 * @file
 * @brief The main file of the elevator application
 */
int main() {
    elevio_init();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    Elevator elevator = initialize();
    printf("last floor is: %d\n", elevator.lastFloor);
    nanosleep(&(struct timespec) {0, 20 * 1000 * 1000}, NULL);

    while (1) {
        check_and_update_elevator_inputs(&elevator); // Update orders in the elevator object
        lights_update_from_orderlist(&elevator);
        set_light_valid_floor_level(&elevator);
        check_state(&elevator);
        nanosleep(&(struct timespec) {0, 20 * 1000 * 1000}, NULL);
    }
}
