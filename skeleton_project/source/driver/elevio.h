#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void);

/**
 * @brief Sets motor direction of the elevator by sending the dirn enumerate over tcp connection to elevator server
 * @param dirn[in] Takes input parameter of the direction of the elevator (-1 is down, 0 is stop, 1 is up)
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Function for setting the ligth of a specific floor button. Specifies floor, button type, and if it is on or off.
 * @param floor[in] int which determines which floor the button is on
 * @param button[in] Enum which specifies what type of button the lights point to
 * @param value[in] Int which states if the light is on or off represented by 0 or 1
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Function for setting the floor indicator based on input
 * @param floor[in] int to specify which floor the light is on
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Function for setting the door light to either on or off based on the boolean value 0 or 1
 * @param value[in] integer representing if the door is open or closed by 0 or 1
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Function for turning on or off the pause button lamp
 * @param value[in] integer representing if the light is on or off (0 or 1)
 */
void elevio_stopLamp(int value);

/**
 * @brief Function for reading if a button is pressed or not by specifying what button to read and receiving a 0 or 1
 * @param floor[in] integer to represent what floor is being checked
 * @param button[in] enum to show what button type is pressed
 * @return buf[out] integer that represents if the specified button is pressed or not by 0 or 1
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Function for reading the sensor output for what floor the elevator is at, or if the elevator is between floors
 * @return buf[out] integer representing the current position of the elevator (-1 for between floors)
 */
int elevio_floorSensor(void);

/**
 * @brief
 * @return
 */
int elevio_stopButton(void);

/**
 * @brief
 * @return
 */
int elevio_obstruction(void);

