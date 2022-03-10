#include "buttons.h"
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "../elevator/elevator.h"
#include "../driver/elevio.h"

void test_clear_all_orders(Elevator *elevator);

{

void test_longjmp(void) {
    jmp_buf buf;
    int i;

    i = setjmp(buf);
    if (i == 0) {
        run_other_func();
        CU_PASS("run_other_func() succeeded.");
    } else
        CU_FAIL("run_other_func() issued longjmp.");
}


Elevator elevator;

void test_clear_all_orders() {
    elevator.orderList[N_FLOORS][N_BUTTONS];
    elevator.orderList[2][2] = 1;
    elevator.orderList[1][0] = 1;

    clear_all_order(&elevator);

    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button < N_BUTTONS; button++) {
//            elevator->orderList[floor][button] = elevio_callButton(floor, button);
            if (elevator.orderList[floor][button] != 0) {
                printf("Error in %d, %d", floor, button);
                hasFailed = 1;
            }
        }
    }
    if (hasFailed == 0) {
        CU_PASS("clear_all_orders() succeeded.");
    } else
        CU_FAIL("clear_all_orders() failed");
}

