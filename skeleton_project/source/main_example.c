#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"



int main_example(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

//    elevio_motorDirection(DIRN_UP);
//    elevator = elevator.Elevator();

    int setFloor = 1;
    int lastFloor = 0;

    while(1){

        int floor = elevio_floorSensor();
        printf("floor: %d , setFloor: %d\n",floor, setFloor);

        if (floor != -1) {
            lastFloor = floor;
        }

        if(setFloor > lastFloor){
            printf("DIRN_UP\n");
            elevio_motorDirection(DIRN_UP);
        }

        if(setFloor < lastFloor){
            printf("DIRN_DOWN\n");
            elevio_motorDirection(DIRN_DOWN);
        }

        if (setFloor == lastFloor) {
            printf("DIRN_STOP\n");

            elevio_motorDirection(DIRN_STOP);
        }

        // Read every button and turn on lamp if button is pressed
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                printf("btnPressed:");
                printf("%d", btnPressed);

                elevio_buttonLamp(f, b, btnPressed);
                if (btnPressed == 1){
                    setFloor = f;
                };

            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
