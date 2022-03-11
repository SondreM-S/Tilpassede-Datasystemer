/**@file
 * @brief
 */

#include <time.h>

time_t timeDoorOpened;

struct Elevator {
    int orderList[N_FLOORS][N_BUTTONS];
    int obstruction;
    int lastFloor;

    enum State {
        movingUp,
        movingDown,
        loading,
        idle,
        stopped
    } state;
    enum Door {
        open,
        closed,
    } door;
    enum LastDirection {
        up,
        down
    } lastDirection;
};
typedef struct Elevator Elevator;

/**@brief Initialize the elevator struct and finds a valid floor
 *
 * @return elevator
 */
Elevator initialize();

/**@brief Check the current state for the elevator, and run the state specific functions
 *
 * @param[in,out] elevator
 */
void check_state(Elevator *elevator);

/**@brief Checks if there is a order at the current floor or in a floor over.
 * If there is no orders there change the last direction to down
 *
 * @param[in,out] elevator
 */

void check_if_stop_at_floor_over(Elevator *elevator);

/**@brief Checks if there is a order at the current floor or in a floor under.
 * If there is no orders change the last direction to up
 *
 * @param[in,out] elevator
 */
void check_if_stop_at_floor_down(Elevator *elevator);

/**@brief Checks if there is any order over the current floor
 *
 * @param[in] currentFloor
 * @param[in] elevator
 * @return 0 if no orders over current floor, 1 if there is orders over current floor
 */
int check_orders_over(int currentFloor, Elevator *elevator);

/**@brief Checks if there is any order under the current floor
 *
 * @param[in] currentFloor
 * @param[in] elevator
 * @return 0 if no orders under current floor, 1 if there is orders under current floor
 */
int check_orders_under(int currentFloor, Elevator *elevator);

/**@brief clears all the orders from the elevator orderlist
 *
 * @param[in,out] elevator
 */
void clear_all_orders(Elevator *elevator);

/**@brief Moves the elevator up and check if it needs to stop at the current floor
 *
 * @param[in,out] elevator
 */
void moving_up_case(Elevator *elevator);

/**@brief Moves the elevator down and check if it needs to stop at the current floor
 *
 * @param[in,out] elevator
 */
void moving_down_case(Elevator *elevator);

/**@brief Open the door wait for 3s and then closes the door
 *
 * @param[in,out] elevator
 */
void loading_case(Elevator *elevator);

/**@brief checks if there is any new orders
 *
 * @param[in,out] elevator
 */
void idle_case(Elevator *elevator);

/**@brief If the stop button is pressed stop the elevator and clears the orderlist
 *
 * @param[in,out] elevator
 */
void stopped_case(Elevator *elevator);