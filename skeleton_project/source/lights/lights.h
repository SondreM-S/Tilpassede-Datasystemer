/** @file
  * @brief Elevator panel light functionality
  *
  */

/** @brief Turns on lights by looping through the elevator orderlist
 *
 * @param elevator elevator object which includes attribute orderlist
 */
void lights_update_from_orderlist(Elevator *elevator);

/**
 *
 * @param elevator
 */
void set_light_valid_floor_level (Elevator *elevator);