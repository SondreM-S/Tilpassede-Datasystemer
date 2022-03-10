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

Elevator initialize();


/**@brief
 *
 * @param elevator
 */
void check_state(Elevator *elevator);

/**@brief
 *
 * @param elevator
 */
void check_if_stop_at_floor(Elevator *elevator);

/**@brief
 *
 * @param currentFloor
 * @param elevator
 * @return
 */
int check_orders_over(int currentFloor, Elevator *elevator);

/**@brief
 *
 * @param currentFloor
 * @param elevator
 * @return
 */
int check_orders_under(int currentFloor, Elevator *elevator);

/**@brief
 *
 * @param elevator
 */
void clear_all_orders(Elevator *elevator);