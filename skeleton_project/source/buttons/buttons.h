/** @file
  * @brief Handling of Button signals
  */


/**
 * @brief Checks the input status of all buttons. Unless the stop button is pressed, this will read all floor buttons and add the pressed buttons to the order
 * list. If the stop button is pressed, the state of the elevator is set to stop, and the function will end.
 * The function also checks the obstruction status and sets the obstruction value in elevator.
 * @param[in,out] elevator is a pointer to the elevator object from struct Elevator in elevator.h
 */
void check_and_update_elevator_inputs(Elevator *elevator);



